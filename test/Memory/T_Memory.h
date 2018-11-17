#include "gtest/gtest.h"
#include "GM.h"
#include "estd/memory_pool.hpp"

namespace GM_Test
{

    class T_Memory : extends(::testing::Test)
    {
    protected:
        void SetUp() override;
        void TearDown() override;

    protected:
        estd::memory_pool<>* m_mem_pool;
    };

}
