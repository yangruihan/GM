#include "gm_value.hpp"

namespace GM
{

    GM_Value::GM_Value () {}
    
    GM_Function* GM_Value::get_func(std::string func_name) const
    {
        if (m_func_dic == nullptr)
            return nullptr;

        auto it = m_func_dic->find(func_name);
        if (it != m_func_dic->end())
        {
            return it->second;
        }

        return nullptr;
    }

}