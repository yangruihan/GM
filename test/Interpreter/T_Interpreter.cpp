#include "T_Interpreter.h"

namespace GM_Test
{

    void T_Interpreter::SetUp()
    {
        interpreter = GM::GM_Interpreter::instance();
    }

    TEST_F(T_Interpreter, InterpreterInstance)
    {
        ASSERT_TRUE(interpreter != nullptr);
    }

}
