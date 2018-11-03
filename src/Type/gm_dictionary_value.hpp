#pragma once

#include "gm_value.hpp"
#include "gm_types.h"

namespace GM
{

    class GM_DictionaryValue : extends(GM_Value)
    {

    public:
        GM_DictionaryValue ();
        virtual ~GM_DictionaryValue ();

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_DICTIONARY_VALUE;
        }

    };

}
