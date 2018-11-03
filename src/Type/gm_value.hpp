#pragma once

#include <string>
#include <map>

#include "../GM.h"
#include "../gm_object.hpp"

class GM_Function;

namespace GM
{

    class GM_Value : extends(GM_Object)
    {

    public:
        GM_Value ();
        ~GM_Value () override = 0;

    public:
        virtual GM_Function* get_func(std::string func_name) const;

    protected:
        static std::map<std::string, GM_Function*>* m_func_dic;

    };

}
