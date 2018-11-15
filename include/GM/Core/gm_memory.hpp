#pragma once

#include "gm_common_header.h"
#include <iostream>

#define C_DEFAULT_ALLOC_BLOCK_SIZE 0x10000

namespace GM
{

    /**
     * Default Allocator use **new** and **delete** key word
     *
     */
    template<size_t DefaultSize = C_DEFAULT_ALLOC_BLOCK_SIZE>
    class GM_DefaultAllocator : extends(GM_Object)
    {
    public:
        static const size_t DEFAULT_ALLOC_BLOCK_SIZE = DefaultSize;

        template<class T>
        T* alloc() { return new T; }

        template<class T>
        T* alloc_arr(const size_t& size) { return new T[size]; }

        template<class T, class ... TArgs>
        T* alloc_args(const TArgs &&... args)
        {
            return new T(std::forward(args)...);
        }

        template<class T, class ... TArgs>
        T* alloc_arr_args(const size_t& size, const TArgs &&... args)
        {
            return new T[size];
        }

        template<class T>
        bool free(T* t)
        {
            delete t;
            return true;
        }

        template<class T>
        bool free_arr(T* t)
        {
            delete[] t;
            return true;
        }
    };

    /**
     * Memory pool with blocks
     *
     */
    template<class Allocator, size_t DefaultSize = Allocator::DEFAULT_ALLOC_BLOCK_SIZE>
    class GM_LegacyMemoryPool : extends(GM_Object)
    {
    private:
        enum block_flag: uint
        {
            BLOCK_FREE  = 0,
            BLOCK_USING = 1,
        };

        /**
         * Memory block struct
         *
         */
        struct block
        {
            size_t      size;   // data size
            block_flag  flag;   // flag for block
            block*      prev;   // pointer to prev block
            block*      next;   // pointer to next block
        };

        static const size_t BLOCK_SIZE = sizeof(block);
        static const uint BLOCK_SIZE_MASK = BLOCK_SIZE - 1;

    public:
        static const size_t DEFAULT_ALLOC_BLOCK_SIZE = DefaultSize;
        static const size_t DEFAULT_ALLOC_MEMORY_SIZE = BLOCK_SIZE * DEFAULT_ALLOC_BLOCK_SIZE;

        GM_LegacyMemoryPool() { _create(); }
        virtual ~GM_LegacyMemoryPool() { _destroy(); }

        template<class T>
        T* alloc() { return static_cast<T*>(_alloc(sizeof(T))); }

        template<class T>
        T* alloc_arr(const size_t& count)
        { return static_cast<T*>(_alloc(count * sizeof(T))); }

        template<class T, class ...TArgs>
        T* alloc_args(const TArgs &&... args)
        {
            T* obj = static_cast<T*>(_alloc(sizeof(T)));
            (*obj)(std::forward(args)...);
            return obj;
        }

        template<class T, class ...TArgs>
        T* alloc_arr_args(const size_t& count, const TArgs &&... args)
        {
            T* obj = static_cast<T*>(_alloc(count * sizeof(T)));
            for (size_t i = 0; i < count; i++)
                (obj[i])(std::forward(args)...);
            return obj;
        }

        template<class T>
        T* realloc(T* obj, const size_t& new_size)
        {
            return static_cast<T*>(_realloc(obj, new_size, sizeof(T)));
        }

        template<class T>
        bool free(T* obj)
        {
            return _free(obj);
        }

        template<class T>
        bool free_array(T* obj)
        {
            return _free(obj);
        }

        size_t available() const { return m_b_free_size; }
        void clear() { _init(); }

        void dump(std::ostream& os)
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
        
    private:
        Allocator m_allocator;
        block* m_b_head = nullptr;
        block* m_b_curt = nullptr;

        size_t m_b_free_size = 0;

        static size_t _block_align(const size_t& size)
        {
            if ((size & BLOCK_SIZE_MASK) == 0)
                return size / BLOCK_SIZE;

            return (size / BLOCK_SIZE) + 1;
        }
        
        static void _block_init(block* b, const size_t& size)
        {
            b->size = size;
            b->flag = block_flag::BLOCK_FREE;
            b->prev = nullptr;
            b->next = nullptr;
        }
        
        static void _block_conn(block* curt, block* next)
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
        static size_t _block_merge(block* curt, block* next)
        {
            next->next->prev = curt;
            curt->next = next->next;
            curt->size += next->size + 1;
            return curt->size;
        }

        static void _block_set_f(block* b, const block_flag& f)
        {
            b->flag = f;
        }

        static uint _block_get_f(const block* b)
        {
            return b->flag;
        }

        void _create()
        {
            m_b_head = m_allocator.template alloc_arr<block>(DEFAULT_ALLOC_BLOCK_SIZE);
            assert(m_b_head);
            _init();
        }
        
        void _init()
        {
            m_b_free_size = DEFAULT_ALLOC_BLOCK_SIZE - 1;
            _block_init(m_b_head, m_b_free_size);
            m_b_head->prev = m_b_head->next = m_b_head;
            m_b_curt = m_b_head;
        }
        
        void _destroy()
        {
            m_allocator.free_arr(m_b_head);
        }

        void* _alloc(const size_t& size)
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
        
        bool _free(void* p)
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
        
        void* _realloc(void* p, const size_t& new_size,
                       const size_t& cls_size)
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

        void* _alloc_free_block(const size_t& size)
        {
            if (m_b_curt->size == size + 1)
                return _alloc_cur_block(size);

            auto new_size = m_b_curt->size - size - 1;
            block* new_block = m_b_curt + size + 1;
            _block_init(new_block, new_size);
            _block_conn(m_b_curt, new_block);
            return _alloc_cur_block(size);
        }
        
        void* _alloc_cur_block(const size_t& size)
        {
            _block_set_f(m_b_curt, block_flag::BLOCK_USING);
            m_b_curt->size = size;
            m_b_free_size -= size + 1;
            auto data = static_cast<void*>(m_b_curt + 1);
            m_b_curt = m_b_curt->next;
            return data;
        }
        
        bool _verify_address(const block* b, const block_flag& flag)
        {
            if (b < m_b_head || b > m_b_head + DEFAULT_ALLOC_BLOCK_SIZE - 1)
                return false;
            return (b->next->prev == b) && (b->prev->next == b) && (_block_get_f(b) == flag);
        }

        static void _dump_block(block* blk, std::ostream& os)
        {
            os << GM_Utils::format_str("Memory Info | [%p-%p] Size: %8zu, State: %s\n", blk, blk + blk->size, blk->size, (_block_get_f(blk) ? "Free" : "Using"));
        }
    };

    template<class Allocator, size_t DefaultSize>
    const size_t GM_LegacyMemoryPool<Allocator, DefaultSize>::BLOCK_SIZE;

    template<class Allocator, size_t DefaultSize>
    const uint GM_LegacyMemoryPool<Allocator, DefaultSize>::BLOCK_SIZE_MASK;

    template<class Allocator, size_t DefaultSize>
    const size_t GM_LegacyMemoryPool<Allocator, DefaultSize>::DEFAULT_ALLOC_BLOCK_SIZE;

    template<class Allocator, size_t DefaultSize>
    const size_t GM_LegacyMemoryPool<Allocator, DefaultSize>::DEFAULT_ALLOC_MEMORY_SIZE;

    /**
     * MemoryPool Allocator
     *
     */
    template<class Allocator = GM_DefaultAllocator<>, size_t DefaultSize = Allocator::DEFAULT_ALLOC_BLOCK_SIZE>
    class GM_LegacyMemoryPoolAllocator : extends(GM_Object)
    {
    public:
        static const size_t DEFAULT_ALLOC_BLOCK_SIZE = DefaultSize - 2;

        template<class T>
        T* alloc()
        {
            return m_memory_pool.template alloc<T>();
        }

        template<class T>
        T* alloc_arr(const size_t& count)
        {
            return m_memory_pool.template alloc_arr<T>(count);
        }

        template<class T, class ... TArgs>
        T* alloc_args(const TArgs &&... args)
        {
            return m_memory_pool.template alloc_args<T>(std::forward(args)...);
        }

        template<class T, class ... TArgs>
        T* alloc_arr_args(const size_t& count, const TArgs &&... args)
        {
            return m_memory_pool.template alloc_arr_args<T>(count, std::forward(args)...);
        }

        template<class T>
        T* realloc(T* t, const size_t& new_size)
        {
            return m_memory_pool.template realloc(t, new_size);
        }

        template<class T>
        bool free(T* t)
        {
            return m_memory_pool.free(t);
        }

        template<class T>
        bool free_arr(T* t)
        {
            return m_memory_pool.free_array(t);
        }

    private:
        GM_LegacyMemoryPool<Allocator, DefaultSize> m_memory_pool;
    };

    template<size_t DefaultSize = GM_DefaultAllocator<>::DEFAULT_ALLOC_BLOCK_SIZE>
    using GM_MemoryPool = GM_LegacyMemoryPool<GM_LegacyMemoryPoolAllocator<GM_DefaultAllocator<DefaultSize>, DefaultSize>>;
}
