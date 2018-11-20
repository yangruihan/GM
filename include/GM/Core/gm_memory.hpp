#pragma once

#include "gm_common_header.h"
#include "estd/memory_pool.hpp"

#include <vector>
#include <utility>

namespace GM
{

    /**
      * Memory Manager for GM
      *
      * ------   ------   ------
      * | 4K | - | 4K | - | 4K |
      * ------   ------   ------
      * chunk    chunk    chunk
      *
      */
    class GM_MemoryManager : extends(GM_Object)
    {
    private:
        struct memory_chunk
        {
            estd::memory_pool<GM_DEFAULT_MEMORY_CHUNK_SIZE>* pool;
            memory_chunk* next;

            memory_chunk()
            {
                pool = new estd::memory_pool<GM_DEFAULT_MEMORY_CHUNK_SIZE>();
            }

            ~memory_chunk()
            {
                delete pool;
            }

            size_t free_size() const
            {
                return pool->available();
            }

            void dump(std::ostream& os) const
            {
                pool->dump(os);
            }
        };
    
    public:
        template<class T = GM_Object>
        static T* alloc()
        {
            return s_ins._alloc<T>();
        }
        
        template<class T = GM_Object>
        static T* alloc_arr(const size_t& count)
        {
            return s_ins._alloc_arr<T>(count);
        }
        
        template<class T = GM_Object, class ...TArgs>
        static T* alloc_args(TArgs &&... args)
        {
            return s_ins._alloc_args<T>(std::forward<TArgs>(args)...);
        }

        template<class T = GM_Object, class ...TArgs>
        static T* alloc_arr_args(const size_t& count, TArgs &&... args)
        {
            return s_ins._alloc_arr_args<T>(count, std::forward<TArgs>(args)...);
        }
        
        template<class T = GM_Object, class Y = GM_Object>
        static Y* realloc(T* obj)
        {
            return s_ins._realloc<T, Y>(obj);
        }

        template<class T>
        static bool free(T*& obj)
        {
            return s_ins._free(obj);
        }

        template<class T>
        static bool free_arr(T*& obj)
        {
            return s_ins._free_arr(obj);
        }
        
        static void dump(std::ostream& os)
        {
            s_ins._dump(os);
        }
        
        static size_t available_size()
        {
            return s_ins._available_size();
        }
        
        static uint16_t get_object_memory_chunk_idx(GM_Object* obj)
        {
            return s_ins._get_object_memory_chunk_idx(obj);
        }
        
    private:
        static GM_MemoryManager s_ins;

    private:
        GM_MemoryManager()
        {
            _new_chunk();
            m_max_alloc_size = GM_DEFAULT_MEMORY_CHUNK_SIZE - estd::BLOCK_SIZE;
        }

        virtual ~GM_MemoryManager()
        {
            for (auto chunk : m_chunks)
                delete chunk;
        }

        GM_MemoryManager(const GM_MemoryManager& other) = delete;

        template<class T = GM_Object>
        T* _alloc()
        {
            auto size = sizeof(T);
            if (size >= m_max_alloc_size)
                return nullptr;

            auto chunk = _get_enough_size_chunk(size, m_curt_memory_idx);
            T* ret = chunk->pool->alloc<T>();
            new (ret) T();
            static_cast<GM_Object*>(ret)->m_memory_chunk_idx = m_curt_memory_idx;
            return ret;
        }

        template<class T = GM_Object>
        T* _alloc_arr(const size_t& count)
        {
            auto size = sizeof(T) * count;
            if (size >= m_max_alloc_size)
                return nullptr;
            auto chunk = _get_enough_size_chunk(size, m_curt_memory_idx);
            T* ret = chunk->pool->alloc_arr<T>(count);
            for (size_t i = 0; i < count; i++)
            {
                auto gm_obj = static_cast<GM_Object*>(ret + i);
                new (ret + i) T();
                gm_obj->m_memory_chunk_idx = m_curt_memory_idx;
            }
            return ret;
        }

        template<class T = GM_Object, class ...TArgs>
        T* _alloc_args(TArgs &&... args)
        {
            auto size = sizeof(T);
            if (size >= m_max_alloc_size)
                return nullptr;

            auto chunk = _get_enough_size_chunk(size, m_curt_memory_idx);
            T* ret = chunk->pool->alloc_args<T>(std::forward<TArgs>(args)...);
            static_cast<GM_Object*>(ret)->m_memory_chunk_idx = m_curt_memory_idx;
            return ret;
        }

        template<class T = GM_Object, class ...TArgs>
        T* _alloc_arr_args(const size_t& count, TArgs &&... args)
        {
            auto size = sizeof(T) * count;
            if (size >= m_max_alloc_size)
                return nullptr;
            auto chunk = _get_enough_size_chunk(size, m_curt_memory_idx);
            T* ret = chunk->pool->alloc_arr_args<T>(count, std::forward<TArgs>(args)...);
            for (size_t i = 0; i < count; i++)
                static_cast<GM_Object*>(ret + i)->m_memory_chunk_idx = m_curt_memory_idx;
            return ret;
        }

        template<class T = GM_Object, class Y = GM_Object>
        Y* _realloc(T* obj)
        {
            // TODO if chunk size is not enough, change a chunk
            auto memory_chunk_idx = static_cast<GM_Object*>(obj)->m_memory_chunk_idx;
            auto chunk = m_chunks[memory_chunk_idx];
            return chunk->pool->realloc<T, Y>(obj);
        }

        template<class T>
        bool _free(T*& obj)
        {
            auto memory_chunk_idx = static_cast<GM_Object*>(obj)->m_memory_chunk_idx;
            auto chunk = m_chunks[memory_chunk_idx];
            auto ret = chunk->pool->free(obj);
            obj = nullptr;
            return ret;
        }

        template<class T>
        bool _free_arr(T*& obj)
        {
            auto memory_chunk_idx = static_cast<GM_Object*>(obj)->m_memory_chunk_idx;
            auto chunk = m_chunks[memory_chunk_idx];
            auto ret = chunk->pool->free_arr(obj);
            obj = nullptr;
            return ret;
        }

    private:
        void _dump(std::ostream& os) const
        {
            os << "\n----------------------------------------------------------------------------------------" << std::endl;
            os << "--- Memory Manager Info ---" << std::endl;
            os << GM_Utils::format_str("- Memory | sum: \t\t%zuB\n", (GM_DEFAULT_MEMORY_CHUNK_SIZE * m_chunks.size()));
            os << GM_Utils::format_str("- Memory | available: \t\t%zuB\n", _available_size());
            os << GM_Utils::format_str("- Memory | chunk count: \t%zu\n", m_chunks.size());
            os << "----------------------------------------------------------------------------------------" << std::endl;
            for (size_t i = 0, count = m_chunks.size(); i < count; i++)
            {
                os << "\n*** Chunk " << i << " ***\n";
                m_chunks[i]->dump(os);
            }
            os << "----------------------------------------------------------------------------------------" << std::endl;
        }

        size_t _available_size() const
        {
            size_t ret = 0;
            for (auto chunk : m_chunks)
                ret += chunk->free_size();

            return ret;
        }

        uint16_t _get_object_memory_chunk_idx(GM_Object* obj) const
        {
            return obj->m_memory_chunk_idx;
        }
    
    private:
        memory_chunk* _get_enough_size_chunk(const size_t& size, uint16_t& memory_chunk_idx)
        {
            auto count = m_chunks.size();
            for (size_t idx = 0; idx < count; idx++)
            {
                if (m_chunks[idx]->free_size() >= size)
                {
                    memory_chunk_idx = idx;
                    return m_chunks[idx];
                }
            }

            memory_chunk_idx = count;
            return _new_chunk();
        }

        memory_chunk* _new_chunk()
        {
            auto new_chunk = new memory_chunk();
            m_chunks.push_back(new_chunk);
            return new_chunk;
        }

    private:
        std::vector<memory_chunk*> m_chunks;
        size_t m_max_alloc_size;
        uint16_t m_curt_memory_idx;
    };

}

using GM_MEM = GM::GM_MemoryManager;
