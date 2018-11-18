#include "T_IntValue.h"

namespace GM_Test
{

    TEST_F(T_IntValue, Base)
    {
        auto env = new GM::GM_Environment();
        ASSERT_NE(nullptr, env);

        auto value = new GM::GM_IntValue(env, "123");
        ASSERT_NE(nullptr, value);
        ASSERT_EQ(123, (int)value->get_value());

        auto value2 = new GM::GM_IntValue(env, 256);
        ASSERT_NE(nullptr, value2);
        ASSERT_EQ(256, (int)value2->get_value());

        auto value3 = new GM::GM_IntValue(env, 12.5);
        ASSERT_NE(nullptr, value3);
        ASSERT_EQ(12, (int)value3->get_value());

        auto value4 = GM::GM_Value::int_value(env, "345");
        ASSERT_NE(nullptr, value4);
        ASSERT_EQ(345, (int)value4->get_value());

        auto value5 = GM::GM_Value::int_value(env, 230);
        ASSERT_NE(nullptr, value5);
        ASSERT_EQ(230, (int)value5->get_value());

        auto value6 = GM::GM_Value::int_value(env, 21.8);
        ASSERT_NE(nullptr, value6);
        ASSERT_EQ(21, (int)value6->get_value());
    }

    TEST_F(T_IntValue, Op)
    {
        auto env = new GM::GM_Environment();
        ASSERT_NE(nullptr, env);

        auto value = new GM::GM_IntValue(env, "123");
        ASSERT_NE(nullptr, value);
        ASSERT_EQ(123, (int)value->get_value());

        auto value2 = new GM::GM_IntValue(env, 256);
        ASSERT_NE(nullptr, value2);
        ASSERT_EQ(256, (int)value2->get_value());

        auto param = new GM::GM_Parameter(env, 2, value, value2);

        auto op = value->get_cur_env_func(FUNC_ADD_OP_KEY);
        ASSERT_NE(nullptr, op);
        auto ret = dynamic_cast<GM::GM_IntValue*>(op->eval(param));
        ASSERT_NE(nullptr, ret);
        ASSERT_EQ(379, (int)ret->get_value());
        delete op;
        delete ret;

        op = value->get_cur_env_func(FUNC_SUB_OP_KEY);
        ASSERT_NE(nullptr, op);
        ret = dynamic_cast<GM::GM_IntValue*>(op->eval(param));
        ASSERT_NE(nullptr, ret);
        ASSERT_EQ(-133, (int)ret->get_value());
        delete op;
        delete ret;

        op = value->get_cur_env_func(FUNC_MUL_OP_KEY);
        ASSERT_NE(nullptr, op);
        ret = dynamic_cast<GM::GM_IntValue*>(op->eval(param));
        ASSERT_NE(nullptr, ret);
        ASSERT_EQ(31488, (int)ret->get_value());
        delete op;
        delete ret;

        op = value->get_cur_env_func(FUNC_DIV_OP_KEY);
        ASSERT_NE(nullptr, op);
        ret = dynamic_cast<GM::GM_IntValue*>(op->eval(param));
        ASSERT_NE(nullptr, ret);
        ASSERT_EQ(0, (int)ret->get_value());
        delete op;
        delete ret;

        GM::GM_BoolValue* bret;
        op = value->get_cur_env_func(FUNC_EQ_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(false, bret->get_value());
        delete op;
        delete bret;

        op = value->get_cur_env_func(FUNC_LS_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(true, bret->get_value());
        delete op;
        delete bret;

        op = value->get_cur_env_func(FUNC_LE_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(true, bret->get_value());
        delete op;
        delete bret;

        op = value->get_cur_env_func(FUNC_GT_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(false, bret->get_value());
        delete op;
        delete bret;

        op = value->get_cur_env_func(FUNC_GE_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(false, bret->get_value());
        delete op;
        delete bret;
    }
}
