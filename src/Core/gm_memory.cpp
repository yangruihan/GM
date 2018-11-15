#include "gm_memory.hpp"
#include "GM.h"

#include <cassert>

#define LEGACY_MEMORY_POOL_FH(ret_type) \
template<class Allocator, size_t DefaultSize> \
ret_type GM_LegacyMemoryPool<Allocator, DefaultSize>

namespace GM
{

    LEGACY_MEMORY_POOL_FH(size_t)::_block_align(const size_t& size)
    {
        if ((size & BLOCK_SIZE_MASK) == 0)
            return size / BLOCK_SIZE;

        return (size / BLOCK_SIZE) + 1;
    }

    LEGACY_MEMORY_POOL_FH(void)::_block_init(block* b, const size_t& size)
    {
        b->size = size;
        b->flag = block_flag::BLOCK_FREE;
        b->prev = nullptr;
        b->next = nullptr;
    }

    LEGACY_MEMORY_POOL_FH(void)::_block_conn(block* curt, block* next)
    {
        next->prev = curt;
        next->next = curt->next;
        next->next->prev = next;
        curt->next = next;
    }

    /**
     *   curt        next
     * ---------   --------
     * |TO FREE| - | FREE |
     * ---------   --------
     *
     */
    LEGACY_MEMORY_POOL_FH(size_t)::_block_merge(block* curt, block* next)
    {
        next->next->prev = curt;
        curt->next = next->next;
        curt->size += next->size + 1;
        return curt->size;
    }

    LEGACY_MEMORY_POOL_FH(void)::_block_set_f(block* b, const block_flag& f)
    {
        b->flag = f;
    }

    LEGACY_MEMORY_POOL_FH(uint)::_block_get_f(const block* b)
    {
        return b->flag;
    }

    LEGACY_MEMORY_POOL_FH(void)::_create()
    {
        m_b_head = m_allocator.template alloc_arr<block>(DEFAULT_ALLOC_BLOCK_SIZE);
        assert(m_b_head);
        _init();
    }

    LEGACY_MEMORY_POOL_FH(void)::_init()
    {
        m_b_free_size = DEFAULT_ALLOC_BLOCK_SIZE - 1;
        _block_init(m_b_head, m_b_free_size);
        m_b_head->prev = m_b_head->next = m_b_head;
        m_b_curt = m_b_head;
    }

    LEGACY_MEMORY_POOL_FH(void)::_destroy()
    {
        m_allocator.free_arr(m_b_head);
    }

    LEGACY_MEMORY_POOL_FH(void*)::_alloc(const size_t& size)
    {
        if (size == 0)
            return nullptr;

        auto aligned_size = _block_align(size);
        if (aligned_size >= m_b_free_size)
        {
            DEBUG_ERROR_F("MemoryNotEnough: current avaialbe(%zu) | need (%zu)", m_b_free_size * BLOCK_SIZE, size);
            return nullptr;
        }

        auto blk = m_b_curt;
        do
        {
            if (_block_get_f(blk) == block_flag::BLOCK_FREE
                && blk->size >= aligned_size + 1)
            {
                m_b_curt = blk;
                return _alloc_free_block(size);
            }
            blk = blk->next;
        } while (blk != m_b_curt);

        return nullptr;
    }

    LEGACY_MEMORY_POOL_FH(void*)::_alloc_free_block(const size_t &size)
    {
        if (m_b_curt->size == size + 1)
            return _alloc_cur_block(size);

        auto new_size = m_b_curt->size - size - 1;
        block* new_block = m_b_curt + size + 1;
        _block_init(new_block, new_size);
        _block_conn(m_b_curt, new_block);
        return _alloc_cur_block(size);
    }

    LEGACY_MEMORY_POOL_FH(void*)::_alloc_cur_block(const size_t &size)
    {
        _block_set_f(m_b_curt, block_flag::BLOCK_USING);
        m_b_curt->size = size;
        m_b_free_size -= size + 1;
        auto data = static_cast<void*>(m_b_curt + 1);
        m_b_curt = m_b_curt->next;
        return data;
    }

    LEGACY_MEMORY_POOL_FH(bool)::_free(void* p)
    {
        auto blk = static_cast<block*>(p);
        blk --; // get block header info
        if (!_verify_address(blk, block_flag::BLOCK_USING))
            return false;

        // just one block
        if (blk->next == blk)
        {
            _block_set_f(blk, block_flag::BLOCK_FREE);
            return true;
        }

        // merge neighbor block
        auto prev_b_mask = _block_get_f(blk->prev) && blk->prev < blk;
        auto next_b_mask = _block_get_f(blk->next) && blk < blk->next;
        auto mask = (prev_b_mask << 1) + next_b_mask;
        auto prev_b = blk->prev;
        auto next_b = blk->next;

        switch (mask)
        {
            case 0:
                m_b_free_size += blk->size + 1;
                _block_set_f(blk, block_flag::BLOCK_FREE);
                break;

            case 1:
                if (m_b_curt == next_b)
                    m_b_curt = blk;
                m_b_free_size += _block_merge(blk, next_b);
                _block_set_f(blk, block_flag::BLOCK_FREE);
                break;

            case 2:
                if (m_b_curt == blk)
                    m_b_curt = prev_b;
                m_b_free_size += _block_merge(prev_b, prev_b->next);
                break;

            case 3:
                if (m_b_curt == blk->next)
                    m_b_curt = blk->prev;
                m_b_free_size += _block_merge(prev_b, blk);
                m_b_free_size += _block_merge(prev_b, next_b);
                break;
        }

        return true;
    }

    LEGACY_MEMORY_POOL_FH(bool)::_verify_address(const GM_LegacyMemoryPool::block* b, const block_flag& flag)
    {
        if (b < m_b_head || b > m_b_head + DEFAULT_ALLOC_BLOCK_SIZE - 1)
            return false;
        return (b->next->prev == b) && (b->prev->next == b) && (_block_get_f(b) == flag);
    }

    LEGACY_MEMORY_POOL_FH(void*)::_realloc(void *p,
                                           const size_t &new_size,
                                           const size_t &cls_size)
    {
        auto blk = static_cast<block*>(p);
        blk --; // get block header info
        if (!_verify_address(blk, block_flag::BLOCK_USING))
            return nullptr;

        // TODO
        // Opt
        // if new_size < current_size split block
        // if new_size > current_size and next block is free
        //   merge next block and this block
        auto aligned_size = _block_align(new_size * cls_size);
        auto alloc_ret = _alloc(aligned_size);
        if (!alloc_ret)
        {
            _free(blk);
            return nullptr;
        }
        auto old_size = blk->size;
        memmove(alloc_ret, p, BLOCK_SIZE *
                (old_size > aligned_size ? aligned_size : old_size));
        _free(p);
        return alloc_ret;
    }

    LEGACY_MEMORY_POOL_FH(void)::dump(std::ostream &os)
    {
        auto ptr = m_b_head;
        os << GM_Utils::format_str("Memory Info | available: %zu\n", m_b_free_size);
        if (ptr->next == ptr)
        {
            if (_block_get_f(ptr) == block_flag::BLOCK_USING)
                _dump_block(ptr, os);
            else
                os << "Memory Info | All Free." << std::endl;
        }
        else
        {
            _dump_block(ptr, os);
            ptr = ptr->next;
            while (ptr != m_b_head)
            {
                _dump_block(ptr, os);
                ptr = ptr->next;
            }
        }
    }

    LEGACY_MEMORY_POOL_FH(void)::_dump_block(GM_LegacyMemoryPool::block *blk, std::ostream &os)
    {
        os << GM_Utils::format_str("Memory Info | [%p-%p] Size: %8zu, State: %s\n", blk, blk + blk->size, blk->size, (_block_get_f(blk) ? "Free" : "Using"));
    }
}
