#include "T_GC.h"

namespace GM_Test
{
    
    TEST_F(T_GC, Base)
    {
        auto env = GM_GC::alloc<GM::GM_Environment>();
        ASSERT_NE(nullptr, env);
        ASSERT_EQ(1, GM_GC::get_ref_cnt(env));

        auto int_value = GM_GC::alloc_args<GM::GM_IntValue>(env, 250);
        ASSERT_NE(nullptr, int_value);
        ASSERT_EQ(1, GM_GC::get_ref_cnt(int_value));

        ASSERT_EQ(2, GM_GC::inc_ref(int_value));
        ASSERT_EQ(2, GM_GC::get_ref_cnt(int_value));

        ASSERT_TRUE(GM_GC::free(int_value));
        ASSERT_EQ(1, GM_GC::get_ref_cnt(int_value));
        ASSERT_TRUE(GM_GC::free(int_value));
        ASSERT_EQ(nullptr, int_value);

        ASSERT_TRUE(GM_GC::free(env));
        ASSERT_EQ(nullptr, env);
    }

}