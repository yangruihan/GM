#pragma once

#include <string>

#include "../GM.h"
#include "../Common/gm_utils.hpp"
#include "gm_number_value.hpp"
#include "gm_list_value.hpp"
#include "gm_types.h"

namespace GM
{

    class GM_IntValue : extends(GM_NumberValue)
    {

    public:
        GM_IntValue (std::string& token);
        GM_IntValue (int value);
        GM_IntValue (double value);
        virtual ~GM_IntValue ();

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_INT_VALUE;
        }

        double get_value() override { return m_value; }
    
    protected:
        int m_value;

        void _init_functions() override;

    private:
        static GM_Value* __add(const GM_ListValue* args);
        static GM_Value* __sub(const GM_ListValue* args);
        static GM_Value* __mul(const GM_ListValue* args);
        static GM_Value* __div(const GM_ListValue* args);
    };
}
