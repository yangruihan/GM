#pragma once

#include <string>

#include "../../gm_common_header.h"
#include "../gm_value.hpp"
#include "../gm_types.h"
#include "../gm_parameter.hpp"

namespace GM
{

    class GM_StrValue : extends(GM_Value)
    {
    public:
        GM_StrValue (std::string& token);
        virtual ~GM_StrValue ();

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_STR_VALUE;
        }
        
        std::string get_value() { return m_value; }
        
        std::string str() const override;
    
    protected:
        std::string m_value;
        
        void _init_functions() override;
        
    private:
        
        static GM_Value* __add(const GM_Parameter* param);
    };
}
