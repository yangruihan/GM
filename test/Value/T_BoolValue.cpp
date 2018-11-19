#include "T_BoolValue.h"

namespace GM_Test
{

    TEST_F(T_BoolValue, Base)
    {
        auto env = new GM::GM_Environment();
        ASSERT_NE(nullptr, env);

        auto value = new GM::GM_BoolValue(env, "false");
        ASSERT_NE(nullptr, value);
        ASSERT_EQ(false, value->get_value());

        auto value1 = new GM::GM_BoolValue(env, true);
        ASSERT_NE(nullptr, value1);
        ASSERT_EQ(true, value1->get_value());

        auto value2 = GM::GM_Value::bool_value(env, "true");
        ASSERT_NE(nullptr, value2);
        ASSERT_EQ(true, value2->get_value());

        auto value3 = GM::GM_Value::bool_value(env, false);
        ASSERT_NE(nullptr, value3);
        ASSERT_EQ(false, value3->get_value());
    }

}
