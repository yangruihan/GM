#pragma once

#include "../../gm_common_header.h"
#include "../gm_types.h"
#include "../gm_value.hpp"

namespace GM
{
    class GM_Environment;

    class GM_NullValue : extends(GM_Value)
    {

    private:
        GM_NullValue (GM_Environment* env);
        ~GM_NullValue() override;

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_NULL_VALUE;
        }

        std::string str() const override
        { return "null"; }

    protected:
        void _init_functions() override;

    public:
        static GM_NullValue* instance;

    };

}
