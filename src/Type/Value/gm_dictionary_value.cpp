#include "gm_dictionary_value.hpp"
#include "../../GM.h"

namespace GM
{

    GM_DictionaryValue::GM_DictionaryValue(GM_Environment* env)
                                            : GM_Value(env)
    {}
    
    GM_DictionaryValue::~GM_DictionaryValue() {}
    
    std::string GM_DictionaryValue::str() const
    {
        return "";
    }
    
    void GM_DictionaryValue::_init_functions()
    {}
 
}
