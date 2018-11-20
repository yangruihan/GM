#pragma once

#include "gtest/gtest.h"
#include "GM.h"

namespace GM_Test
{

    class T_BoolValue : extends(::testing::Test)
    {
    protected:
        void SetUp() override;
        void TearDown() override;
    };

}
