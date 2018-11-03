#include "gm_object.hpp"
#include "Common/gm_errors.hpp"
#include "Common/gm_utils.hpp"

#define extends(class_name) public class_name
#define implements(class_name) public class_name

namespace GM
{

    class GM_Value;
    class GM_ListValue;

    typedef GM_Value* (*GM_FUNCTION_PTR)(const GM_ListValue*);

}