#include "T_Interpreter.h"

namespace GM_Test
{

    void T_Interpreter::SetUp()
    {
        m_interpreter = GM::GM_Interpreter::instance();
    }

    void T_Interpreter::TearDown()
    {
        GM::GM_Interpreter::destory();
    }

    TEST_F(T_Interpreter, InterpreterInstance)
    {
        ASSERT_TRUE(m_interpreter != nullptr);
    }

    TEST_F(T_Interpreter, InterpreterFiles)
    {
    #ifdef COMMAND_LINE
        ASSERT_EQ(m_interpreter->parse_file("demo/flow_ctrl.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("demo/func_closure.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("demo/func_recursion.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("demo/func_var.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("demo/func.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("demo/hello_world.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("demo/inner_func.gm"), 0);
    #else
        ASSERT_EQ(m_interpreter->parse_file("../../../demo/flow_ctrl.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("../../../demo/func_closure.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("../../../demo/func_recursion.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("../../../demo/func_var.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("../../../demo/func.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("../../../demo/hello_world.gm"), 0);
        ASSERT_EQ(m_interpreter->parse_file("../../../demo/inner_func.gm"), 0);
    #endif
    }

}
