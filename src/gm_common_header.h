#pragma once

#include "gm_object.hpp"
#include "Common/gm_errors.hpp"
#include "Common/gm_utils.hpp"

#define extends(class_name) public class_name
#define implements(class_name) public class_name

#define FUNC_ADD_OP_KEY "__add"
#define FUNC_SUB_OP_KEY "__sub"
#define FUNC_MUL_OP_KEY "__mul"
#define FUNC_DIV_OP_KEY "__div"

namespace GM
{
    
    class GM_Value;
    class GM_Parameter;
    
    typedef GM_Value* (*GM_FUNCTION_PTR)(GM_Parameter*);
    
}
