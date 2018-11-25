#include "gm_null_value.hpp"

#include "GM.h"

namespace GM
{

    GM_NullValue* GM_NullValue::s_ins;

    GM_NullValue::GM_NullValue(GM_Environment* env): GM_Value(env) {}

    GM_NullValue::~GM_NullValue() = default;

    void GM_NullValue::init(GM_Environment* env)
    {
        if (s_ins == nullptr)
        {
            s_ins = GM_GC::alloc_args<GM_NullValue>(env);
            GCINC(s_ins);
        }
    }

    void GM_NullValue::destroy()
    {
        GCFREE(s_ins);
    }

    void GM_NullValue::_init_functions() {}

}
