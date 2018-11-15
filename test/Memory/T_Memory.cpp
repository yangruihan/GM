#include "T_Memory.h"

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
    }
}
