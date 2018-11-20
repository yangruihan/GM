#pragma once

#include "gtest/gtest.h"
#include "GM.h"

namespace GM_Test
{

    class T_GC : extends(::testing::Test)
    {
    protected:
        void SetUp() override;
        void TearDown() override;
    };

}
