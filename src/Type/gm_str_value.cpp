#include "gm_str_value.hpp"
#include "../Common/gm_utils.hpp"

namespace GM
{
    
    GM_StrValue::GM_StrValue(std::string& token): m_value(token)
    {}
    
    GM_StrValue::~GM_StrValue() {}
    
    void GM_StrValue::_init_functions()
    {

    }
    
    std::string GM_StrValue::str()
    {
        return GM_Utils::format_str("%s", m_value.c_str());
    }
    
    GM_Value *GM_StrValue::__add(const GM_ListValue *args)
    {
        
    }

}
