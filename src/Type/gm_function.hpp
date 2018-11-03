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
        GM_Function ();
        virtual ~GM_Function ();

    protected:
        // function name
        std::string m_name;

        // function pointer
        GM_Value* (*m_function)(const GM_ListValue*);
    };

}
