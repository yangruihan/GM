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

    TEST_F(T_Interpreter, InterpreterFiles)
    {
        ASSERT_EQ(interpreter->parse_file("demo/flow_ctrl.gm"), 0);
        ASSERT_EQ(interpreter->parse_file("demo/func_closure.gm"), 0);
        ASSERT_EQ(interpreter->parse_file("demo/func_recursion.gm"), 0);
        ASSERT_EQ(interpreter->parse_file("demo/func_var.gm"), 0);
        ASSERT_EQ(interpreter->parse_file("demo/func.gm"), 0);
        ASSERT_EQ(interpreter->parse_file("demo/hello_world.gm"), 0);
        ASSERT_EQ(interpreter->parse_file("demo/inner_func.gm"), 0);
    }

}
