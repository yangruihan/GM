#include "gm_custom_function_value.hpp"

#include "GM.h"
#include <sstream>

namespace GM
{

    GM_CustomFuncValue::GM_CustomFuncValue(GM_Environment*                 env,
                                           const std::string&              func_name,
                                           const size_t&                   param_count,
                                           const std::vector<std::string>* param_list,
                                           GM_AST_TREE*                    func_body)
                                           : GM_Value(env),
                                             m_func_name(func_name),
                                             m_param_count(param_count),
                                             m_param_names(param_list),
                                             m_func_body(func_body)
    {
        GCINC(m_func_body);
    }

    GM_CustomFuncValue::~GM_CustomFuncValue()
    {
        delete m_param_names;
        GCFREE(m_func_body);
    }
    
    void GM_CustomFuncValue::_init_functions() {}

    std::string GM_CustomFuncValue::_str() const
    {
        std::ostringstream stream;
        stream << "[" << m_func_name << " (";

        for (size_t i = 0, count = m_param_names->size() - 1; i < count; i++)
            stream << (*m_param_names)[i] << ", ";
        stream << (*m_param_names)[m_param_names->size() - 1] << ")]";

        return stream.str();
    }

    bool GM_CustomFuncValue::check_func_name_valid(const std::string &func_name)
    {
        return !GM_Utils::is_digit(func_name[0]);
    }

    GM_Value* GM_CustomFuncValue::eval()
    {
        const auto ret = m_func_body->eval();
        const auto list_value = dynamic_cast<GM_ListValue*>(ret);
        if (list_value == nullptr)
            return ret;

        return (*list_value)[list_value->get_item_count() - 1];
    }

}
