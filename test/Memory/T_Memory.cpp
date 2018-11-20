#include "T_Memory.h"

#include <iostream>
#include <string>

namespace GM_Test
{

    void T_Memory::SetUp()
    {
        m_mem_pool = new estd::memory_pool<>();
    }

    void T_Memory::TearDown()
    {
        delete m_mem_pool;
    }

    TEST_F(T_Memory, BaseTypeAllocAndFree)
    {
        ASSERT_NE(nullptr, m_mem_pool);
        int* i = m_mem_pool->alloc<int>();
        *i = 100;
        ASSERT_EQ(*i, 100);
        *i = 28;
        ASSERT_EQ(*i, 28);
        ASSERT_TRUE(m_mem_pool->free(i));
        ASSERT_FALSE(m_mem_pool->free(i));
        ASSERT_FALSE(m_mem_pool->free<int>(nullptr));
        ASSERT_EQ(nullptr, m_mem_pool->alloc_arr<int>(0x100000));
        ASSERT_EQ(i, m_mem_pool->alloc<int>());
        ASSERT_EQ(28, *i);
        auto j = m_mem_pool->alloc<int>();
        *j = 52;
        ASSERT_EQ(*j, 52);
        ASSERT_EQ(*j + *i, 80);
        auto k = m_mem_pool->alloc<int>();
        // align 8
        auto size_int = 0;
        if ((sizeof(int) & 0x7) == 0)
            size_int = sizeof(int);
        else
            size_int = ((sizeof(int) >> 3) + 1) << 3;
        ASSERT_EQ(estd::BLOCK_SIZE + size_int, (j - i) * sizeof(int));
        ASSERT_EQ(estd::BLOCK_SIZE + size_int, (k - j) * sizeof(int));
        ASSERT_TRUE(m_mem_pool->free(i));
        ASSERT_TRUE(m_mem_pool->free(j));
        ASSERT_TRUE(m_mem_pool->free(k));
        for (size_t i = 0; i < (4096 / (estd::BLOCK_SIZE + size_int)); i++)
            m_mem_pool->alloc<int>();
        ASSERT_EQ(nullptr, m_mem_pool->alloc<int>());
    }

    TEST_F(T_Memory, ComTypeAllocAndFree)
    {
        ASSERT_NE(nullptr, m_mem_pool);
        int* i[] =
        {
            m_mem_pool->alloc<int>(),
            m_mem_pool->alloc_arr<int>(500),
            m_mem_pool->alloc<int>(),
        };
        *(i[0]) = 1;
        *(i[1]) = 2;
        *(i[2]) = 3;
        ASSERT_EQ(1, *(i[0]));
        ASSERT_EQ(nullptr, m_mem_pool->alloc_arr<int>(500));
        ASSERT_TRUE(m_mem_pool->free(i[1]));
        ASSERT_TRUE(m_mem_pool->free(i[2]));
        i[1] = m_mem_pool->alloc_arr<int>(500);
        *(i[1] + 2) = 100;
        ASSERT_EQ(100, *(i[1] + 2));
        ASSERT_NE(nullptr, i[1]);
        ASSERT_EQ(2, *(i[1]));
        i[2] = m_mem_pool->alloc_arr<int>(489);
        ASSERT_NE(nullptr, i[2]);
        ASSERT_EQ(3, *(i[2]));
        auto k = m_mem_pool->alloc<int>();
        ASSERT_EQ(nullptr, k);
        ASSERT_TRUE(m_mem_pool->free(i[0]));
        ASSERT_TRUE(m_mem_pool->free(i[2]));
        ASSERT_TRUE(m_mem_pool->free(i[1]));
        auto j = m_mem_pool->alloc<int>();
        ASSERT_NE(nullptr, j);
        *j = 500;
        ASSERT_EQ(500, *j);
        ASSERT_TRUE(m_mem_pool->free(j));
    }

    TEST_F(T_Memory, GM_MemoryManagerBaseTypeAllocAndFree)
    {
        GM::GM_Environment* env = GM_MEM::alloc<GM::GM_Environment>();
        ASSERT_NE(nullptr, env);
        GM::GM_IntValue* intValue = GM_MEM::alloc_args<GM::GM_IntValue>(env, "100");
        ASSERT_NE(nullptr, intValue);
        ASSERT_EQ(100, (int)intValue->get_value());
        ASSERT_EQ(nullptr, env->get_parent());
        GM::GM_StrValue* strValue = GM_MEM::alloc_args<GM::GM_StrValue>(env, "hello world");
        ASSERT_NE(nullptr, strValue);
        ASSERT_STREQ(strValue->get_value().c_str(), "hello world");
        ASSERT_TRUE(GM_MEM::free(intValue));
        ASSERT_EQ(nullptr, intValue);
        intValue = GM_MEM::alloc_args<GM::GM_IntValue>(env, 250);
        ASSERT_EQ(250, (int)intValue->get_value());
        ASSERT_EQ(0, GM_MEM::get_object_memory_chunk_idx(intValue));

        GM_MEM::free(intValue);
        GM_MEM::free(strValue);
        ASSERT_EQ(GM_MEM::available_size(), GM_DEFAULT_MEMORY_CHUNK_SIZE - estd::BLOCK_SIZE - sizeof(GM::GM_Environment));

        auto count = (GM_DEFAULT_MEMORY_CHUNK_SIZE - estd::BLOCK_SIZE * 2 - sizeof(GM::GM_Environment)) / sizeof(GM::GM_IntValue);

        GM::GM_IntValue* intValues = GM_MEM::alloc_arr_args<GM::GM_IntValue>(count, env, 1);
        ASSERT_NE(nullptr, intValues);
        ASSERT_EQ(1, (int)intValues->get_value());
        ASSERT_EQ(1, (int)(intValues + 5)->get_value());
        ASSERT_EQ(1, (int)(intValues + 50)->get_value());
        ASSERT_EQ(1, (int)(intValues + 124)->get_value());
        auto intValue_5 =(GM::GM_Object*)(intValues + 5);
        ASSERT_FALSE(GM_MEM::free(intValue_5));
        ASSERT_EQ(GM_MEM::available_size(), 0);

        GM::GM_IntValue* intValue2 = GM_MEM::alloc_args<GM::GM_IntValue>(env, 20);
        ASSERT_NE(nullptr, intValue2);
        ASSERT_EQ(20, (int)intValue2->get_value());
        ASSERT_EQ(1, GM_MEM::get_object_memory_chunk_idx(intValue2));
        ASSERT_EQ(GM_MEM::available_size(), GM_DEFAULT_MEMORY_CHUNK_SIZE - estd::BLOCK_SIZE - sizeof(GM::GM_IntValue));

        ASSERT_TRUE(GM_MEM::free(intValues));

        GM::GM_IntValue* intValue3 = GM_MEM::alloc_args<GM::GM_IntValue>(env, 36);
        ASSERT_EQ(36, (int)intValue3->get_value());
        ASSERT_EQ(0, GM_MEM::get_object_memory_chunk_idx(intValue3));
        ASSERT_TRUE(GM_MEM::free(intValue3));
        ASSERT_EQ(nullptr, intValue3);
    }
    
}
