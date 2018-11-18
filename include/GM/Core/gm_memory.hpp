#pragma once

#include "gm_common_header.h"
#include "estd/memory_pool.hpp"

#include <vector>
#include <forward_list>

namespace GM
{

    class GM_MemoryManager : extends(GM_Object)
    {
    private:
        struct memory_chunk
        {
            estd::memory_pool<GM_DEFAULT_MEMORY_CHUNK_SIZE>* self;
            memory_chunk* next;

            memory_chunk()
            {
                self = new estd::memory_pool<GM_DEFAULT_MEMORY_CHUNK_SIZE>();
            }

            ~memory_chunk()
            {
                delete self;
            }

            size_t free_size() const
            {
                return self->available();
            }
        };

    public:
        GM_MemoryManager()
        {
            _new_chunk();
            m_max_alloc_size = GM_DEFAULT_MEMORY_CHUNK_SIZE - estd::BLOCK_SIZE;
        }

        virtual ~GM_MemoryManager()
        {
            for (auto chunk : chunks)
                delete chunk;
        }

        GM_MemoryManager(const GM_MemoryManager& other) = delete;

        template<class T = GM_Object>
        T* alloc()
        {
            auto size = sizeof(T);
            if (size >= m_max_alloc_size)
                return nullptr;

            auto chunk = _get_enough_size_chunk(size, m_curt_memory_idx);
            T* ret = chunk->self->alloc<T>();
            static_cast<GM_Object*>(ret)->m_memory_chunk_idx = m_curt_memory_idx;
            return ret;
        }

        template<class T = GM_Object>
        T* alloc_arr(const size_t& count)
        {
            auto size = sizeof(T) * count;
            if (size >= m_max_alloc_size)
                return nullptr;
            auto chunk = _get_enough_size_chunk(size, m_curt_memory_idx);
            T* ret = chunk->self->alloc_arr<T>(count);
            for (size_t i = 0; i < count; i++)
                static_cast<GM_Object*>(ret + i)->m_memory_chunk_idx = m_curt_memory_idx;
            return ret;
        }

        template<class T = GM_Object, class ...TArgs>
        T* alloc_args(const TArgs &&... args)
        {
            auto size = sizeof(T);
            if (size >= m_max_alloc_size)
                return nullptr;

            auto chunk = _get_enough_size_chunk(size, m_curt_memory_idx);
            T* ret = chunk->self->alloc_args<T>(std::forward(args)...);
            static_cast<GM_Object*>(ret)->m_memory_chunk_idx = m_curt_memory_idx;
            return ret;
        }

        template<class T = GM_Object, class ...TArgs>
        T* alloc_arr_args(const size_t& count, const TArgs &&... args)
        {
            auto size = sizeof(T) * count;
            if (size >= m_max_alloc_size)
                return nullptr;
            auto chunk = _get_enough_size_chunk(size, m_curt_memory_idx);
            T* ret = chunk->self->alloc_arr_args<T>(count, std::forward(args)...);
            for (size_t i = 0; i < count; i++)
                static_cast<GM_Object*>(ret + i)->m_memory_chunk_idx = m_curt_memory_idx;
            return ret;
        }

        template<class T = GM_Object, class Y = GM_Object>
        Y* realloc(T* obj)
        {
            // TODO if chunk size is not enough, change a chunk
            auto memory_chunk_idx = static_cast<GM_Object*>(obj)->m_memory_chunk_idx;
            auto chunk = chunks[memory_chunk_idx];
            return chunk->self->realloc<T, Y>(obj);
        }

        template<class T>
        bool free(T* obj)
        {
            auto memory_chunk_idx = static_cast<GM_Object*>(obj)->m_memory_chunk_idx;
            auto chunk = chunks[memory_chunk_idx];
            return chunk->self->free(obj);
        }

        template<class T>
        bool free_arr(T* obj)
        {
            auto memory_chunk_idx = static_cast<GM_Object*>(obj)->m_memory_chunk_idx;
            auto chunk = chunks[memory_chunk_idx];
            return chunk->self->free_arr(obj);
        }

    private:
        memory_chunk* _get_enough_size_chunk(const size_t& size, uint16_t& memory_chunk_idx)
        {
            for (auto chunk : chunks)
                if (chunk->free_size() >= size)
                    return chunk;

            auto count = chunks.size();
            for (size_t idx = 0; idx < count; idx++)
            {
                if (chunks[idx]->free_size() >= size)
                {
                    memory_chunk_idx = idx;
                    return chunks[idx];
                }
            }

            memory_chunk_idx = count;
            return _new_chunk();
        }

        memory_chunk* _new_chunk()
        {
            auto new_chunk = new memory_chunk();
            chunks.push_back(new_chunk);
            return new_chunk;
        }

        std::vector<memory_chunk*> chunks;
        size_t m_max_alloc_size;
        uint16_t m_curt_memory_idx;
    };

}
