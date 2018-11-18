#pragma once

#include "gtest/gtest.h"
#include "GM.h"

namespace GM_Test
{

    class T_Interpreter : extends(::testing::Test)
    {
    protected:
        void SetUp() override;
        void TearDown() override;

    protected:
        GM::GM_Interpreter* m_interpreter;
    };

}
