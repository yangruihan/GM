#include "T_Memory.h"
#include <iostream>

namespace GM_Test
{

    void T_Memory::SetUp()
    {
        m_mem_pool = new GM::GM_MemoryPool<10>();
    }

    void T_Memory::TearDown()
    {
        delete m_mem_pool;
    }

    TEST_F(T_Memory, BaseTypeAllocAndFree)
    {
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
        ASSERT_EQ(0x40, (j - i) * sizeof(int));
        ASSERT_EQ(0x40, (k - j) * sizeof(int));
        m_mem_pool->alloc<int>();
        ASSERT_EQ(nullptr, m_mem_pool->alloc<int>());
    }

    TEST_F(T_Memory, ComTypeAllocAndFree)
    {
        int* i[] =
        {
            m_mem_pool->alloc<int>(),
            m_mem_pool->alloc_arr<int>(32),
            m_mem_pool->alloc<int>(),
        };
        *(i[0]) = 1;
        *(i[1]) = 2;
        *(i[2]) = 3;
        ASSERT_EQ(1, *(i[0]));
        ASSERT_EQ(nullptr, m_mem_pool->alloc_arr<int>(32));
        ASSERT_TRUE(m_mem_pool->free(i[1]));
        ASSERT_TRUE(m_mem_pool->free(i[2]));
        i[1] = m_mem_pool->alloc_arr<int>(32);
        *(i[1] + 2) = 100;
        ASSERT_EQ(100, *(i[1] + 2));
        ASSERT_NE(nullptr, i[1]);
        ASSERT_EQ(2, *(i[1]));
        i[2] = m_mem_pool->alloc_arr<int>(8);
        ASSERT_NE(nullptr, i[2]);
        ASSERT_EQ(3, *(i[2]));
        i[3] = m_mem_pool->alloc<int>();
        ASSERT_EQ(nullptr, i[3]);
        ASSERT_TRUE(m_mem_pool->free(i[0]));
        ASSERT_TRUE(m_mem_pool->free(i[2]));
        ASSERT_TRUE(m_mem_pool->free(i[1]));
        auto j = m_mem_pool->alloc<int>();
        ASSERT_NE(nullptr, j);
        *j = 500;
        ASSERT_EQ(500, *j);
    }
}
