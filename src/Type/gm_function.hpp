#pragma once

#include <string>

#include "../GM.h"
#include "../gm_object.hpp"
#include "gm_list_value.hpp"
#include "gm_value.hpp"

class GM_Value;

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

    protected:
        // function name
        std::string m_name;

        // function pointer
        GM_FUNCTION_PTR m_function;
    };

}
