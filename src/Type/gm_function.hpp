#pragma once

#include <string>

#include "../gm_common_header.h"
#include "gm_value.hpp"
#include "gm_parameter.hpp"

namespace GM
{

    class GM_Function : extends(GM_Object)
    {

    public:
        GM_Function (const std::string func_name, const GM_FUNCTION_PTR func);
        virtual ~GM_Function ();
    
    public:
        static GM_Function* create_func(const std::string name, const GM_FUNCTION_PTR func);

        std::string get_name() const { return m_name; }

        GM_FUNCTION_PTR get_func() const { return m_function; }

        GM_Value* eval(GM_Parameter* parameter) const;

    protected:
        // function name
        std::string m_name;

        // function pointer
        GM_FUNCTION_PTR m_function;
    };

}
