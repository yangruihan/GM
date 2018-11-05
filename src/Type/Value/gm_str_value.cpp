#include "gm_str_value.hpp"
#include "../../GM.h"

namespace GM
{
    
    GM_StrValue::GM_StrValue(GM_Environment* env,
                             const std::string& token)
                             : GM_Value(env), m_value(token)
    {
        _init_functions();
    }
    
    GM_StrValue::~GM_StrValue() {}
    
    void GM_StrValue::_init_functions()
    {
        GM_Value::set_func(GM_Function::create_func(FUNC_ADD_OP_KEY,
                                                    2,
                                                    GM_StrValue::__add));
    }
    
    std::string GM_StrValue::str() const
    {
        return GM_Utils::format_str("%s", m_value.c_str());
    }
    
    GM_Value *GM_StrValue::__add(const GM_Parameter *param)
    {
        auto str_arg1 = param->get_param<GM_Value>(0);
        auto str_arg2 = param->get_param<GM_Value>(1);
        
        if (str_arg1 == nullptr || str_arg2 == nullptr)
            return nullptr;

        return GM_Value::str_value(str_arg1->get_environment(),
                                   str_arg1->str() + str_arg2->str());
    }

}
