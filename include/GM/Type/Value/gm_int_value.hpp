#pragma once

#include <string>

#include "../../Core/gm_common_header.h"
#include "gm_number_value.hpp"
#include "../gm_parameter.hpp"
#include "../gm_types.h"

namespace GM
{
    class GM_Environment;

    class GM_IntValue : extends(GM_NumberValue)
    {

    public:
        GM_IntValue (GM_Environment* env,
                     const std::string& token);
        GM_IntValue (GM_Environment* env,
                     int value);
        GM_IntValue (GM_Environment* env,
                     double value);
        virtual ~GM_IntValue ();

    public:
        GM_VALUE_STR_FUNC(GM_IntValue)

        std::string _str() const override;

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
        GM_STATIC_FUNCTION_D(__add);
        GM_STATIC_FUNCTION_D(__sub);
        GM_STATIC_FUNCTION_D(__mul);
        GM_STATIC_FUNCTION_D(__div);

        GM_STATIC_FUNCTION_D(__ls);     // <
        GM_STATIC_FUNCTION_D(__eq);     // =
        GM_STATIC_FUNCTION_D(__gt);     // >
        GM_STATIC_FUNCTION_D(__le);     // <=
        GM_STATIC_FUNCTION_D(__ge);     // >=
        GM_STATIC_FUNCTION_D(__ne);     // !=
    };
}
