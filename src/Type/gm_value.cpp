#include "gm_value.hpp"
#include "gm_function.hpp"

namespace GM
{
    
    GM_Function* GM_Value::get_func(std::string func_name) const
    {
        auto it = m_func_dic.find(func_name);
        if (it != m_func_dic.end())
        {
            return it->second;
        }

        return nullptr;
    }

    void GM_Value::set_func(GM_Function* func)
    {
        if (func == nullptr)
        {
            PRINT_ERROR("Nullptr Error: func is nullptr");
            return;
        }

        m_func_dic[func->get_name()] = func;
    }

}