#include "gm_function.hpp"
#include "gm_memory.hpp"

namespace GM
{

    GM_Function::GM_Function(GM_Environment*       env,
                             const std::string&    func_name,
                             const int&            param_count,
                             const GM_FUNCTION_PTR func)
    : GM_Value(env), m_name(func_name), m_param_count(param_count), m_function(func)
    {}

    GM_Function::~GM_Function()
    {}

    GM_Function* GM_Function::create_func(GM_Environment*       env,
                                          const std::string&    name,
                                          const int&            param_count,
                                          const GM_FUNCTION_PTR func)
    {
        return GM_GC::alloc_args<GM_Function>(env, name, param_count, func);
    }

    GM_Value* GM_Function::eval(GM_Parameter* parameter) const
    {
        return (*get_func())(parameter);
    }

}
