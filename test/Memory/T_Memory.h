#include "gtest/gtest.h"
#include "GM.h"

namespace GM_Test
{

    class T_Memory : extends(::testing::Test)
    {
    protected:
        void SetUp() override;
        void TearDown() override;

    protected:
        GM::GM_MemoryPool<10>* m_mem_pool;
    };

}
