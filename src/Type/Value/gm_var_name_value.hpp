#pragma once

#include "../../gm_common_header.h"
#include "../gm_value.hpp"

namespace GM
{

    class GM_VarNameValue : extends(GM_Value)
    {
    public:
        GM_VarNameValue (GM_Environment* env,
                     const std::string& var_name);
        virtual ~GM_VarNameValue ();

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_VAR_NAME_VALUE;
        }

        std::string get_var_name() const { return m_var_name; }

        std::string str() const override;

    protected:
        const std::string m_var_name;

        void _init_functions() override;
    };

}