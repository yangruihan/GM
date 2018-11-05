#pragma once

#include "../../gm_common_header.h"
#include "../gm_value.hpp"

namespace GM
{

    class GM_AST_LIST_EXPR;

    class GM_CustomFuncValue : extends(GM_Value)
    {

    public:
        GM_CustomFuncValue (GM_Environment* env,
                            const std::string func_name,
                            GM_AST_LIST_EXPR* param_list,
                            GM_AST_LIST_EXPR* func_body);
        virtual ~GM_CustomFuncValue ();

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_CUST_FUNC_VALUE;
        }

        std::string str() const override;

    protected:
        void _init_functions() override;

    protected:
        std::string func_name;
        GM_AST_LIST_EXPR* param_list;
        GM_AST_LIST_EXPR* func_body;

    };

}
