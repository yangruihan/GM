#pragma once

#include "../../gm_common_header.h"
#include "../gm_value.hpp"

namespace GM
{

    class GM_DictionaryValue : extends(GM_Value)
    {

    public:
        GM_DictionaryValue ();
        ~GM_DictionaryValue() override;

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_DICTIONARY_VALUE;
        }
        
        std::string str() const override;
        
    protected:
        void _init_functions() override;
        
    };

}
