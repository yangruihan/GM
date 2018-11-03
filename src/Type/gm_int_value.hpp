#pragma once

#include "../GM.h"
#include "gm_number_value.hpp"

namespace GM
{

    class GM_IntValue : extends(GM_NumberValue)
    {

    public:
        GM_IntValue ();
        virtual ~GM_IntValue ();

    public:
        float get_value() override;
    
    };

}
