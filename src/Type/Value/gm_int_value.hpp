#pragma once

#include <string>

#include "../../gm_common_header.h"
#include "gm_number_value.hpp"
#include "../gm_parameter.hpp"
#include "../gm_types.h"

namespace GM
{

    class GM_IntValue : extends(GM_NumberValue)
    {

    public:
        GM_IntValue (const std::string& token);
        GM_IntValue (int value);
        GM_IntValue (double value);
        virtual ~GM_IntValue ();

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_INT_VALUE;
        }

        double get_value() override { return m_value; }

        std::string str() const override;
    
    protected:
        int m_value;

        void _init_functions() override;

    private:
        static GM_Value* __add(const GM_Parameter* args);
        static GM_Value* __sub(const GM_Parameter* args);
        static GM_Value* __mul(const GM_Parameter* args);
        static GM_Value* __div(const GM_Parameter* args);
    };
}
