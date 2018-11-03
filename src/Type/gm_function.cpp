#include "gm_function.hpp"

namespace GM
{

    GM_Function::GM_Function(const std::string func_name, const GM_FUNCTION_PTR func) 
    : m_name(func_name), m_function(func) {}

    GM_Function::~GM_Function() {}

    GM_Function* GM_Function::create_func(const std::string name, 
                                          const GM_FUNCTION_PTR func)
    {
        return new GM_Function(name, func);
    }

    GM_Value* GM_Function::eval(GM_ListValue* parameters) const
    {
        return (*get_func())(parameters);
    }

}