#pragma once

#include "../GM.h"
#include "gm_value.hpp"

namespace GM
{

    class GM_NumberValue : extends(GM_Value)
    {

    public:
        GM_NumberValue ();
        virtual ~GM_NumberValue ();

    public:
        virtual float get_value() = 0;

    };

}
