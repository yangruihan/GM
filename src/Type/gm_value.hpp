#pragma once

#include <string>
#include <map>

#include "../GM.h"
#include "../gm_object.hpp"
#include "gm_types.h"

namespace GM
{
    class GM_Function;

    class GM_Value : extends(GM_Object)
    {

    public:
        GM_Value ();
        ~GM_Value () override = 0;

    public:
        GM_Function* get_func(std::string func_name) const;

        void set_func(GM_Function* func);

        virtual VALUE_TYPE get_type() const 
        { 
            return T_GM_VALUE; 
        }

    protected:
        virtual void _init_functions() = 0;

    protected:
        VALUE_TYPE value_type;

    protected:
        std::map<std::string, GM_Function*> m_func_dic;

    };

}
