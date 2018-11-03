#pragma once

#include "../GM.h"
#include "gm_value.hpp"
#include "gm_types.h"

namespace GM
{

    class GM_NumberValue : extends(GM_Value)
    {

    public:
        GM_NumberValue () {}
        virtual ~GM_NumberValue () {}

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_NUMBER_VALUE;
        }

        virtual double get_value() = 0;

    };

}
