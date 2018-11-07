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
        GM_Function (const std::string func_name,
                     const int& param_count,
                     const GM_FUNCTION_PTR func);
        virtual ~GM_Function ();
    
    public:
        static GM_Function* create_func(const std::string name,
                                         const int& param_count,
                                         const GM_FUNCTION_PTR func);

        std::string str() const override
        {
            return GM_Utils::format_str("[$GM_Function, name:%s]",
                                        get_name().c_str());
        }

        std::string get_name() const { return m_name; }

        int get_param_count() const { return m_param_count; }

        GM_FUNCTION_PTR get_func() const { return m_function; }

        GM_Value* eval(GM_Parameter* parameter) const;

    protected:
        // function name
        const std::string m_name;

        // function parameters count
        const int m_param_count;

        // function pointer
        const GM_FUNCTION_PTR m_function;
    };

}
