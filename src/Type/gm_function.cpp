#include "gm_function.hpp"

namespace GM
{

    GM_Function::GM_Function(const std::string func_name,
                             const int& param_count,
                             const GM_FUNCTION_PTR func)
    : m_name(func_name), m_param_count(param_count), m_function(func)
    {}

    GM_Function::~GM_Function() {}

    GM_Function* GM_Function::create_func(const std::string name,
                                          const int& param_count,
                                          const GM_FUNCTION_PTR func)
    {
        return new GM_Function(name, param_count, func);
    }

    GM_Value* GM_Function::eval(GM_Parameter* parameter) const
    {
        return (*get_func())(parameter);
    }

}
