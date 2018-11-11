#include "gtest/gtest.h"
#include "GM.h"

namespace GM_Test
{

    class T_Interpreter : public ::testing::Test
    {
    protected:
        void SetUp() override;

    protected:
        GM::GM_Interpreter* interpreter;
    };

}
