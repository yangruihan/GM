#pragma once

#include "../gm_common_header.h"
#include "gm_number_value.hpp"
#include "gm_parameter.hpp"
#include "gm_types.h"

namespace GM
{

    class GM_FloatValue : extends(GM_NumberValue)
    {

    public:
        GM_FloatValue (std::string& token);
        GM_FloatValue (int value);
        GM_FloatValue (double value);

        virtual ~GM_FloatValue () {};

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_FLOAT_VALUE;
        }

        double get_value() override { return m_value; }

        std::string str() const override;

    protected:
        void _init_functions() override;

    protected:
        double m_value;

    private:
        static GM_Value* __add(GM_Parameter* args);
        static GM_Value* __sub(GM_Parameter* args);
        static GM_Value* __mul(GM_Parameter* args);
        static GM_Value* __div(GM_Parameter* args);

    };

}
