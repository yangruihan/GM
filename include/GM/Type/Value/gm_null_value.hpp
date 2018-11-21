#pragma once

#include "../../Core/gm_common_header.h"
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
        GM_VALUE_DEBUG_STR_FUNC(GM_NullValue)
        GM_VALUE_STR_FUNC(null)

        std::string _str() const override
        { return "null"; }

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_NULL_VALUE;
        }

    protected:
        void _init_functions() override;

    public:
        static GM_NullValue instance;

    };

}
