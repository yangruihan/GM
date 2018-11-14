#pragma once

#include "gm_common_header.h"

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

}
