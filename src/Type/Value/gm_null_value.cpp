#include "gm_null_value.hpp"

#include "../../GM.h"

namespace GM
{

    GM_NullValue::GM_NullValue() {}

    GM_NullValue::~GM_NullValue() {}

    void GM_NullValue::_init_functions() {}

    GM_NullValue* GM_NullValue::instance = new GM_NullValue();
}
