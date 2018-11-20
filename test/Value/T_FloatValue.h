#pragma once

#include "gtest/gtest.h"
#include "GM.h"

namespace GM_Test
{
    
    class T_FloatValue : extends(::testing::Test)
    {
    protected:
        void SetUp() override;
        void TearDown() override;
    };

}