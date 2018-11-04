#pragma once

#include <string>
#include <map>

#include "../gm_common_header.h"
#include "gm_types.h"

namespace GM
{
    class GM_Function;

    class GM_Value : extends(GM_Object)
    {

    public:
        GM_Value () {}
        virtual ~GM_Value () {};

    public:
        GM_Function* get_func(std::string func_name) const;

        void set_func(GM_Function* func);

        virtual VALUE_TYPE get_type() const 
        { 
            return T_GM_VALUE; 
        }

        virtual std::string str() const = 0;

    protected:
        virtual void _init_functions() = 0;

    protected:
        VALUE_TYPE value_type;

    protected:
        std::map<std::string, GM_Function*> m_func_dic;

    };

}
