#include "gm_custom_function.hpp"

#include "../../GM.h"
#include <sstream>

namespace GM
{

    GM_CustomFuncValue::GM_CustomFuncValue(GM_Environment* env,
                                           const std::string func_name,
                                           GM_AST_LIST_EXPR* param_list,
                                           GM_AST_LIST_EXPR* func_body)
                                           : GM_Value(env),
                                             func_name(func_name),
                                             param_list(param_list),
                                             func_body(func_body)
    {}

    GM_CustomFuncValue::~GM_CustomFuncValue() {}
    
    void GM_CustomFuncValue::_init_functions() {}

    std::string GM_CustomFuncValue::str() const
    {
        std::ostringstream stream;
        stream << "[" << func_name << param_list->token_list_str() << "]";
        return stream.str();
    }

}
