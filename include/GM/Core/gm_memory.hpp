#pragma once

#include "gm_common_header.h"
#include "estd/memory_pool.hpp"

#include <vector>
#include <utility>
#include <algorithm>

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

            bool check_space(const size_t& size) const
            {
                return pool->check_space(size);
            }

            size_t available_size() const
            {
                return pool->available_size();
            }

            size_t free_size() const
            {
                return pool->free_size();
            }

            void dump(std::ostream& os, estd::dump_obj_handler dump_obj_handler = nullptr) const
            {
                pool->dump(os, dump_obj_handler);
            }
        };
    
    public:
        static void init()
        {
            if (s_ins == nullptr)
                s_ins = new GM_MemoryManager();
        }

        static void destory()
        {
            delete s_ins;
            s_ins = nullptr;
        }

        template<class T = GM_Object>
        static T* alloc()
        {
            return s_ins->_alloc<T>();
        }
        
        template<class T = GM_Object>
        static T* alloc_arr(const size_t& count)
        {
            return s_ins->_alloc_arr<T>(count);
        }
        
        template<class T = GM_Object, class ...TArgs>
        static T* alloc_args(TArgs &&... args)
        {
            return s_ins->_alloc_args<T>(std::forward<TArgs>(args)...);
        }

        template<class T = GM_Object, class ...TArgs>
        static T* alloc_arr_args(const size_t& count, TArgs &&... args)
        {
            return s_ins->_alloc_arr_args<T>(count, std::forward<TArgs>(args)...);
        }
        
        template<class T = GM_Object, class Y = GM_Object>
        static Y* realloc(T* obj)
        {
            return s_ins->_realloc<T, Y>(obj);
        }

        template<class T>
        static bool free(T*& obj)
        {
            return s_ins->_free(obj);
        }

        template<class T>
        static bool free_arr(T*& obj)
        {
            return s_ins->_free_arr(obj);
        }
        
        static void dump(std::ostream& os, estd::dump_obj_handler dump_obj_handler = nullptr)
        {
            s_ins->_dump(os, dump_obj_handler);
        }
        
        static size_t available_size()
        {
            return s_ins->_available_size();
        }

        static size_t free_size()
        {
            return s_ins->_free_size();
        }
        
        static uint16_t get_object_memory_chunk_idx(GM_Object* obj)
        {
            return obj->m_memory_chunk_idx;
        }
        
    private:
        static GM_MemoryManager* s_ins;

    public:
        GM_MemoryManager(const GM_MemoryManager& other) = delete;
        GM_MemoryManager operator=(const GM_MemoryManager& other) = delete;

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

        template<class T = GM_Object>
        T* _alloc()
        {
            const auto size = sizeof(T);
            if (size >= m_max_alloc_size)
                return nullptr;

            uint16_t memory_idx = 0;
            auto chunk = _get_enough_size_chunk(size, memory_idx);
            T* ret = chunk->pool->alloc<T>();
            new (ret) T();
            static_cast<GM_Object*>(ret)->m_memory_chunk_idx = memory_idx;
            return ret;
        }

        template<class T = GM_Object>
        T* _alloc_arr(const size_t& count)
        {
            auto size = sizeof(T) * count;
            if (size >= m_max_alloc_size)
                return nullptr;

            uint16_t memory_idx = 0;
            auto chunk = _get_enough_size_chunk(size, memory_idx);
            T* ret = chunk->pool->alloc_arr<T>(count);
            for (size_t i = 0; i < count; i++)
            {
                const auto gm_obj = static_cast<GM_Object*>(ret + i);
                new (ret + i) T();
                gm_obj->m_memory_chunk_idx = memory_idx;
            }
            return ret;
        }

        template<class T = GM_Object, class ...TArgs>
        T* _alloc_args(TArgs &&... args)
        {
            const auto size = sizeof(T);
            if (size >= m_max_alloc_size)
                return nullptr;

            uint16_t memory_idx = 0;
            auto chunk = _get_enough_size_chunk(size, memory_idx);
            T* ret = chunk->pool->alloc_args<T>(std::forward<TArgs>(args)...);
            static_cast<GM_Object*>(ret)->m_memory_chunk_idx = memory_idx;
            return ret;
        }

        template<class T = GM_Object, class ...TArgs>
        T* _alloc_arr_args(const size_t& count, TArgs &&... args)
        {
            auto size = sizeof(T) * count;
            if (size >= m_max_alloc_size)
                return nullptr;

            uint16_t memory_idx = 0;
            auto chunk = _get_enough_size_chunk(size, memory_idx);
            T* ret = chunk->pool->alloc_arr_args<T>(count, std::forward<TArgs>(args)...);
            for (size_t i = 0; i < count; i++)
                static_cast<GM_Object*>(ret + i)->m_memory_chunk_idx = memory_idx;
            return ret;
        }

        template<class T = GM_Object, class Y = GM_Object>
        Y* _realloc(T* obj)
        {
            // TODO if chunk size is not enough, change a chunk
            const auto memory_chunk_idx = static_cast<GM_Object*>(obj)->m_memory_chunk_idx;
            auto chunk = m_chunks[memory_chunk_idx];
            return chunk->pool->realloc<T, Y>(obj);
        }

        template<class T>
        bool _free(T*& ref)
        {
            auto obj = static_cast<GM_Object*>(ref);
            auto chunk = m_chunks[obj->m_memory_chunk_idx];
            obj->m_memory_chunk_idx = 0;
            auto ret = chunk->pool->free(obj);
            ref = nullptr;
            return ret;
        }

        template<class T>
        bool _free_arr(T*& ref)
        {
            auto obj = static_cast<GM_Object*>(ref);
            auto chunk = m_chunks[obj->m_memory_chunk_idx];
            obj->m_memory_chunk_idx = 0;
            auto ret = chunk->pool->free_arr(obj);
            ref = nullptr;
            return ret;
        }

    private:
        void _dump(std::ostream& os, estd::dump_obj_handler dump_obj_handler = nullptr) const
        {
            os << "\n----------------------------------------------------------------------------------------" << std::endl;
            os << "-------- Memory Manager Info --------" << std::endl;
            os << GM_Utils::format_str("- Memory | sum: \t\t%zuB\n", GM_DEFAULT_MEMORY_CHUNK_SIZE * m_chunks.size());
            os << GM_Utils::format_str("- Memory | free: \t\t%zuB\n", _free_size());
            os << GM_Utils::format_str("- Memory | available: \t\t%zuB\n", _available_size());
            os << GM_Utils::format_str("- Memory | chunk count: \t%zu\n", m_chunks.size());
            os << "----------------------------------------------------------------------------------------" << std::endl;
            for (size_t i = 0, count = m_chunks.size(); i < count; i++)
            {
                os << "\n*** Chunk " << i << " ***\n";
                m_chunks[i]->dump(os, dump_obj_handler);
            }
            os << "----------------------------------------------------------------------------------------" << std::endl;
        }

        size_t _available_size() const
        {
            size_t ret = 0;
            for (auto chunk : m_chunks)
                ret += chunk->available_size();

            return ret;
        }

        size_t _free_size() const
        {
            size_t ret = 0;
            for (auto chunk : m_chunks)
                ret += chunk->free_size();

            return ret;
        }
    
    private:
        memory_chunk* _get_enough_size_chunk(const size_t& size, uint16_t& memory_chunk_idx)
        {
            const auto count = m_chunks.size();
            for (size_t idx = 0; idx < count; idx++)
            {
                if (m_chunks[idx]->check_space(size))
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
            const auto new_chunk = new memory_chunk();
            m_chunks.push_back(new_chunk);
            return new_chunk;
        }

    private:
        std::vector<memory_chunk*> m_chunks;
        size_t                     m_max_alloc_size;
    };

    class GM_GarbageCollector : extends(GM_Object)
    {
    public:
        static void init()
        {
            GM_MemoryManager::init();

            if (s_ins == nullptr)
                s_ins = new GM_GarbageCollector();
        }

        static void destroy()
        {
            GM_MemoryManager::destory();
            delete s_ins;
            s_ins = nullptr;
        }

        template<class T = GM_Object>
        static T* alloc()
        {
            auto obj = GM_MemoryManager::alloc<T>();
            _init_new_obj((GM_Object*)obj);
            return obj;
        }

        template<class T = GM_Object, class ...TArgs>
        static T* alloc_args(TArgs &&... args)
        {
            auto obj = GM_MemoryManager::alloc_args<T>(std::forward<TArgs>(args)...);
            _init_new_obj((GM_Object*)obj);
            return obj;
        }
        
        template<class T>
        static bool free(T*& obj)
        {
            const auto ref = static_cast<GM_Object*>(obj);
            if (ref->m_ref_cnt == 0)
            {
                PRINT_ERROR("GCFatal: obj ref count is already 0");
                return false;
            }
            else if (ref->m_ins_idx < GM_DEFAULT_INS_IDX_START)
            {
                PRINT_ERROR("GCFatal: obj is not alloc by GCAllocator");
                return false;
            }

            if (dec_ref(ref) == 0)
                obj = nullptr;
            return true;
        }

        static void dump(std::ostream& os, estd::dump_obj_handler dump_obj_handler = nullptr)
        {
            GM_MemoryManager::dump(os, dump_obj_handler);
        }

        static uint64_t inc_ref(GM_Object* obj)
        {
            obj->m_ref_cnt++;
            return obj->m_ref_cnt;
        }

        static uint64_t dec_ref(GM_Object* obj, bool delay_free = false)
        {
            if (obj->m_ins_idx < GM_DEFAULT_INS_IDX_START)
            {
                PRINT_ERROR("GCFatal: obj is not alloc by GCAllocator");
                return 0;
            }

            obj->m_ref_cnt--;
            if (!delay_free && obj->m_ref_cnt == 0)
            {
                const auto it = std::find(s_ins->m_objs.begin(), s_ins->m_objs.end(), obj);
                
                if (it != s_ins->m_objs.end())
                {
                    s_ins->m_objs.erase(it);
                }
//                else
//                {
//                    PRINT_ERROR("GCFatal: obj is not in managered memory");
//                    return 0;
//                }

                obj->m_ins_idx = 0;
                obj->~GM_Object();
                GM_MemoryManager::free(obj);
                return 0;
            }
            return obj->m_ref_cnt;
        }

        static uint64_t get_ref_cnt(const GM_Object* obj)
        {
            return obj->m_ref_cnt;
        }

        static uint64_t get_ref_cnt(GM_Object* obj)
        {
            return obj->m_ref_cnt;
        }

        static uint64_t get_ins_idx(const GM_Object* obj)
        {
            return obj->m_ins_idx;
        }

        static uint64_t get_ins_idx(GM_Object* obj)
        {
            return obj->m_ins_idx;
        }

        static bool check_obj_valid(GM_Object* obj)
        {
            return obj != nullptr && obj->m_ref_cnt > 0 && obj->m_ins_idx >= GM_DEFAULT_INS_IDX_START;
        }

        static bool check_obj_valid(const GM_Object* obj)
        {
            return obj != nullptr && obj->m_ref_cnt > 0 && obj->m_ins_idx >= GM_DEFAULT_INS_IDX_START;
        }

        static void gc()
        {
            std::vector<GM_Object*> wait_to_free_list;

            for (int i = s_ins->m_objs.size() - 1; i >= 0; i--)
            {
                auto obj = s_ins->m_objs[i];
                if (obj->m_ref_cnt == 0)
                {
                    s_ins->m_objs.erase(s_ins->m_objs.begin() + i);
                    wait_to_free_list.push_back(obj);
                }
            }

            for (auto& obj : wait_to_free_list)
            {
                obj->m_ins_idx = 0;
                obj->~GM_Object();
                GM_MemoryManager::free(obj);
            }
        }

    private:
        static void _init_new_obj(GM_Object* obj)
        {
            obj->m_ref_cnt = 0;
            obj->m_ins_idx = _get_valid_ins_idx();
            s_ins->m_objs.push_back(obj);
        }

        static uint64_t _get_valid_ins_idx()
        {
            return s_ins_idx_counter++;
        }

        static GM_GarbageCollector* s_ins;
        static uint64_t             s_ins_idx_counter;
        
        std::vector<GM_Object*>     m_objs;

    };

}

using GM_MEM = GM::GM_MemoryManager;
using GM_GC  = GM::GM_GarbageCollector;
