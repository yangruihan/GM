#include "T_GC.h"

namespace GM_Test
{
    
    void T_GC::SetUp()
    {
        GM_GC::init();
    }

    void T_GC::TearDown()
    {
        GM_GC::destroy();
    }

    TEST_F(T_GC, Base)
    {
        auto env = GM::GM_Environment::create(nullptr);
        ASSERT_NE(nullptr, env);
        ASSERT_EQ(0, GCREFCNF(env));
        ASSERT_EQ(1, GCINC(env));
        ASSERT_EQ(1, GCREFCNF(env));

        auto int_value = GM_GC::alloc_args<GM::GM_IntValue>(env, 250);
        ASSERT_NE(nullptr, int_value);
        ASSERT_EQ(0, GCREFCNF(int_value));
        ASSERT_EQ(1, GCINC(int_value));

        ASSERT_EQ(2, GCINC(int_value));
        ASSERT_EQ(2, GCREFCNF(int_value));

        ASSERT_TRUE(GCFREE(int_value));
        ASSERT_EQ(1, GCREFCNF(int_value));
        ASSERT_TRUE(GCFREE(int_value));
        ASSERT_EQ(nullptr, int_value);

        GM::GM_Environment::clear(env);
        ASSERT_TRUE(GCFREE(env));
        ASSERT_EQ(nullptr, env);
    }

}
