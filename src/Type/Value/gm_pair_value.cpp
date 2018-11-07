#include "gm_pair_value.hpp"

#include "../../GM.h"

namespace GM
{

    GM_PairValue::GM_PairValue (GM_Environment* env,
                                const std::string& key,
                                GM_Object* value)
        : GM_Value(env), m_key(key), m_value(value)
    { }

    GM_PairValue::~GM_PairValue () {}
        
    std::string GM_PairValue::_str() const
    {
        return GM_Utils::format_str("(\"%s\": %s)",
                                  m_key.c_str(),
                                  m_value->str().c_str());
    }
    
    void GM_PairValue::_init_functions()
    {}

}
