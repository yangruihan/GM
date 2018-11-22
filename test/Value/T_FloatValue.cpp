#include "T_FloatValue.h"

namespace GM_Test
{
   
    void T_FloatValue::SetUp()
    {
        GM_GC::init();
    }

    void T_FloatValue::TearDown()
    {
        GM_GC::destroy();
    }
    
    TEST_F(T_FloatValue, Base)
    {
        auto env = GM::GM_Environment::create(nullptr);
        ASSERT_NE(nullptr, env);

        auto value = GM_GC::alloc_args<GM::GM_FloatValue>(env, "123.2");
        ASSERT_NE(nullptr, value);
        ASSERT_FLOAT_EQ(123.2, value->get_value());

        auto value2 = GM_GC::alloc_args<GM::GM_FloatValue>(env, 256);
        ASSERT_NE(nullptr, value2);
        ASSERT_FLOAT_EQ(256.0, value2->get_value());

        auto value3 = GM_GC::alloc_args<GM::GM_FloatValue>(env, 12.5);
        ASSERT_NE(nullptr, value3);
        ASSERT_FLOAT_EQ(12.5, value3->get_value());

        auto value4 = GM::GM_Value::float_value(env, "345.8");
        ASSERT_NE(nullptr, value4);
        ASSERT_FLOAT_EQ(345.8, value4->get_value());

        auto value5 = GM::GM_Value::float_value(env, 230);
        ASSERT_NE(nullptr, value5);
        ASSERT_FLOAT_EQ(230.0, value5->get_value());

        auto value6 = GM::GM_Value::float_value(env, 21.8);
        ASSERT_NE(nullptr, value6);
        ASSERT_FLOAT_EQ(21.8, value6->get_value());

        ASSERT_TRUE(GM_GC::free(value));
        ASSERT_TRUE(GM_GC::free(value2));
        ASSERT_TRUE(GM_GC::free(value3));
        ASSERT_TRUE(GM_GC::free(value4));
        ASSERT_TRUE(GM_GC::free(value5));
        ASSERT_TRUE(GM_GC::free(value6));
        GM::GM_Environment::clear(env);
    }

    TEST_F(T_FloatValue, Op)
    {
        auto env = GM::GM_Environment::create(nullptr);
        ASSERT_NE(nullptr, env);

        auto value = GM_GC::alloc_args<GM::GM_FloatValue>(env, "123.2");
        ASSERT_NE(nullptr, value);
        ASSERT_FLOAT_EQ(123.2, value->get_value());

        auto value2 = GM_GC::alloc_args<GM::GM_FloatValue>(env, 256.4);
        ASSERT_NE(nullptr, value2);
        ASSERT_FLOAT_EQ(256.4, value2->get_value());

        auto param = GM_GC::alloc_args< GM::GM_Parameter>(env, 2, value, value2);

        auto op = value->get_cur_env_func(FUNC_ADD_OP_KEY);
        ASSERT_NE(nullptr, op);
        auto ret = dynamic_cast<GM::GM_FloatValue*>(op->eval(param));
        ASSERT_NE(nullptr, ret);
        ASSERT_FLOAT_EQ(379.6, ret->get_value());
        GM_GC::free(ret);

        op = value->get_cur_env_func(FUNC_SUB_OP_KEY);
        ASSERT_NE(nullptr, op);
        ret = dynamic_cast<GM::GM_FloatValue*>(op->eval(param));
        ASSERT_NE(nullptr, ret);
        ASSERT_FLOAT_EQ(-133.2, ret->get_value());
        GM_GC::free(ret);

        op = value->get_cur_env_func(FUNC_MUL_OP_KEY);
        ASSERT_NE(nullptr, op);
        ret = dynamic_cast<GM::GM_FloatValue*>(op->eval(param));
        ASSERT_NE(nullptr, ret);
        ASSERT_FLOAT_EQ(31588.48, ret->get_value());
        GM_GC::free(ret);

        op = value->get_cur_env_func(FUNC_DIV_OP_KEY);
        ASSERT_NE(nullptr, op);
        ret = dynamic_cast<GM::GM_FloatValue*>(op->eval(param));
        ASSERT_NE(nullptr, ret);
        ASSERT_FLOAT_EQ(0.480499219968799f, ret->get_value());
        GM_GC::free(ret);

        op = value->get_cur_env_func(FUNC_EQ_OP_KEY);
        ASSERT_NE(nullptr, op);
        GM::GM_BoolValue * bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(false, bret->get_value());
        GM_GC::free(bret);

        op = value->get_cur_env_func(FUNC_LS_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(true, bret->get_value());
        GM_GC::free(bret);

        op = value->get_cur_env_func(FUNC_LE_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(true, bret->get_value());
        GM_GC::free(bret);

        op = value->get_cur_env_func(FUNC_GT_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(false, bret->get_value());
        GM_GC::free(bret);

        op = value->get_cur_env_func(FUNC_GE_OP_KEY);
        ASSERT_NE(nullptr, op);
        bret = dynamic_cast<GM::GM_BoolValue*>(op->eval(param));
        ASSERT_NE(nullptr, bret);
        ASSERT_EQ(false, bret->get_value());
        GM_GC::free(bret);

        GM::GM_Environment::clear(env);
    }

}