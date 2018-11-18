#include "T_BoolValue.h"

namespace GM_Test
{

    TEST_F(T_BoolValue, Base)
    {
        GM::GM_Environment* env = new GM::GM_Environment();
        ASSERT_NE(nullptr, env);
        ASSERT_TRUE("false" == "false");
        GM::GM_BoolValue* value = new GM::GM_BoolValue(env, "false");
        ASSERT_NE(nullptr, value);
        ASSERT_EQ(false, value->get_value());
        GM::GM_BoolValue* value1 = new GM::GM_BoolValue(env, true);
        ASSERT_NE(nullptr, value1);
        ASSERT_EQ(true, value1->get_value());
    }

}
