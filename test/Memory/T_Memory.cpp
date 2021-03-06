#include "T_Memory.h"

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
    
}
