#pragma once

#include "../../Core/gm_common_header.h"
#include "../gm_types.h"
#include "../gm_value.hpp"

namespace GM
{
    class GM_Environment;

    class GM_BoolValue : extends(GM_Value)
    {

    public:
        GM_BoolValue (GM_Environment* env,
                      const std::string& token);
        GM_BoolValue (GM_Environment* env,
                      const char* token);
        GM_BoolValue (GM_Environment* env,
                      const bool& value);
        ~GM_BoolValue() override {}

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_BOOL_VALUE;
        }

        void set_value(const bool& value) { m_value = value; }
        bool get_value() const { return m_value; }

    public:
        GM_VALUE_DEBUG_STR_FUNC(GM_BoolValue)
        GM_VALUE_STR_FUNC(bool)

        std::string _str() const override;

    protected:
        void _init_functions() override;

    protected:
        bool m_value;
    };

}
