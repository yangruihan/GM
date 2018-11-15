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
    class GM_DefaultAllocator : extends(GM_Object)
    {
    public:
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
    template<class Allocator, size_t DefaultSize = C_DEFAULT_ALLOC_BLOCK_SIZE>
    class GM_LegacyMemoryPool : extends(GM_Object)
    {
    public:
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

        void dump(std::ostream& os);
        
    private:
        Allocator m_allocator;
        block* m_b_head = nullptr;
        block* m_b_curt = nullptr;

        size_t m_b_free_size = 0;

        static size_t _block_align(const size_t& size);
        static void _block_init(block* b, const size_t& size);
        static void _block_conn(block* curt, block* next);
        static size_t _block_merge(block* curt, block* next);

        static void _block_set_f(block* b, const block_flag& f);
        static uint _block_get_f(const block* b);

        void _create();
        void _init();
        void _destroy();
        void* _alloc(const size_t& size);
        bool _free(void* p);
        void* _realloc(void* p, const size_t& new_size,
                       const size_t& cls_size);

        void* _alloc_free_block(const size_t& size);
        void* _alloc_cur_block(const size_t& size);
        bool _verify_address(const block* b, const block_flag& flag);

        static void _dump_block(block* blk, std::ostream& os);
    };

    /**
     * MemoryPool Allocator
     *
     */
    template<class Allocator = GM_DefaultAllocator, size_t DefaultSize = C_DEFAULT_ALLOC_BLOCK_SIZE>
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

    template<size_t DefaultSize = C_DEFAULT_ALLOC_BLOCK_SIZE>
    using GM_MemoryPool = GM_LegacyMemoryPool<GM_LegacyMemoryPoolAllocator<GM_DefaultAllocator, DefaultSize>>;
}
