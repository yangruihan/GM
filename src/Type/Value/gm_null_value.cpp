#include "gm_null_value.hpp"

#include "GM.h"

namespace GM
{

    GM_NullValue::GM_NullValue(GM_Environment* env): GM_Value(env) {}

    GM_NullValue::~GM_NullValue() = default;

    void GM_NullValue::_init_functions() {}

    GM_NullValue GM_NullValue::instance = GM_NullValue(nullptr);

}
