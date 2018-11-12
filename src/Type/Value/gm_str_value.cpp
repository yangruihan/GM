#include "gm_str_value.hpp"
#include "GM.h"

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
        GM_VALUE_SET_SELF_FUNCTION(FUNC_ADD_OP_KEY, 2, GM_StrValue::__add);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_GET_OP_KEY, 2, GM_StrValue::__get);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_SET_OP_KEY, 3, GM_StrValue::__set);
    }
    
    std::string GM_StrValue::_str() const
    {
        return GM_Utils::format_str("%s", m_value.c_str());
    }

    std::string GM_StrValue::get(const size_t &index) const
    {
        if (index > m_value.size())
            return "";

        return std::string(1, m_value[index]);
    }

    GM_StrValue* GM_StrValue::set(const size_t &index, const char &value)
    {
        if (index < m_value.size())
            m_value[index] = value;

        return this;
    }
    
    GM_FUNCTION_I(GM_StrValue, __add)
    {
        GET_PARAM(self, GM_StrValue, 0);
        GET_VALUE_PARAM(other, 1);

        return GM_Value::str_value(param->get_environment(),
                                   self->_str() + other->_str());
    }

    GM_FUNCTION_I(GM_StrValue, __get)
    {
        GET_PARAM(self,  GM_StrValue, 0);
        GET_PARAM(index, GM_IntValue, 1);

        auto ret = self->get((size_t)index->get_value());
        return GM_Value::str_value(param->get_environment(), ret);
    }

    GM_FUNCTION_I(GM_StrValue, __set)
    {
        GET_PARAM(self,  GM_StrValue, 0);
        GET_PARAM(index, GM_IntValue, 1);
        GET_PARAM(value, GM_StrValue, 2);

        self->set((size_t)index->get_value(), value->get_value()[0]);
        return self;
    }

}
