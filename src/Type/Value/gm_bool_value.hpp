#pragma once

#include "../../gm_common_header.h"
#include "../gm_types.h"
#include "../gm_value.hpp"

namespace GM
{

    class GM_BoolValue : extends(GM_Value)
    {

    public:
        GM_BoolValue (const std::string& token);
        ~GM_BoolValue() override {}

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_BOOL_VALUE;
        }

        std::string str() const override;

    protected:
        void _init_functions() override;

    protected:
        bool m_value;
    };

}
