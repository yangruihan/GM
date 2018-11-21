#pragma once

#include "../../Core/gm_common_header.h"
#include "../gm_value.hpp"
#include <vector>

namespace GM
{

    class GM_AST_TREE;

    class GM_CustomFuncValue : extends(GM_Value)
    {

    public:
        GM_CustomFuncValue (GM_Environment* env,
                            const std::string& func_name,
                            const size_t& param_count,
                            const std::vector<std::string>* param_list,
                            GM_AST_TREE* func_body);
        virtual ~GM_CustomFuncValue ();
    public:
        GM_VALUE_DEBUG_STR_FUNC(GM_CustomFuncValue)
        GM_VALUE_STR_FUNC(function)

        std::string _str() const override;

    public:
        static bool check_func_name_valid(const std::string& func_name);

        VALUE_TYPE get_type() const override
        {
            return T_GM_CUST_FUNC_VALUE;
        }

        size_t get_param_count() const { return m_param_count; }

        std::string get_param_name(const size_t& index) const
        {
            if (index >= m_param_names->size())
            {
                PRINT_ERROR_F("IndexError: get param name, index(%zu) out of range(%zu)",
                              index, m_param_names->size());
                return "";
            }

            return (*m_param_names)[index];
        }

        GM_AST_TREE* get_func_body() const { return m_func_body; }

        GM_Value* eval();

    protected:
        void _init_functions() override;

    protected:
        const std::string m_func_name;
        const size_t m_param_count;
        const std::vector<std::string>* m_param_names;
        GM_AST_TREE* m_func_body;

    };

}
