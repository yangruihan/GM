#pragma once

#include <string>
#include <map>
#include <vector>

#include "../Core/gm_common_header.h"
#include "gm_types.h"

namespace GM
{
    class GM_Object;
    class GM_Environment;
    class GM_Function;

    class GM_NullValue;
    class GM_BoolValue;
    class GM_StrValue;
    class GM_IntValue;
    class GM_FloatValue;
    class GM_ListValue;
    class GM_PairValue;
    class GM_DictValue;
    class GM_VarNameValue;
    class GM_CustomFuncValue;
    class GM_AST_TREE;

    class GM_Value : extends(GM_Object)
    {

    public:
        GM_Value (GM_Environment* env);
        virtual ~GM_Value ();

    public:
        static GM_Value* convert_to_value(GM_Object* obj);

        GM_Environment* get_environment() const { return m_environment; }

        GM_Function* get_func(const std::string& func_name) const;

        GM_Function* get_cur_env_func(const std::string& func_name) const;

        void set_func(GM_Function* func);

        virtual VALUE_TYPE get_type() const 
        { 
            return T_GM_VALUE; 
        }

    public:
        GM_VALUE_STR_FUNC(GM_Value)

        virtual std::string _str() const = 0;

    protected:
        virtual void _init_functions() {};

    protected:
        GM_Environment* m_environment;

    public:
        /* --- get value --- */
        static GM_NullValue* null_value ();

        static GM_BoolValue* bool_value (GM_Environment* env,
                                         const std::string& token);
        static GM_BoolValue* bool_value (GM_Environment* env,
                                         const bool& value);

        static GM_StrValue* str_value (GM_Environment* env,
                                       const std::string& token);

        static GM_IntValue* int_value (GM_Environment* env,
                                       const std::string& token);
        static GM_IntValue* int_value (GM_Environment* env,
                                       const int& value);
        static GM_IntValue* int_value (GM_Environment* env,
                                       const double& value);

        static GM_FloatValue* float_value (GM_Environment* env,
                                           const std::string& token);
        static GM_FloatValue* float_value (GM_Environment* env,
                                           int value);
        static GM_FloatValue* float_value (GM_Environment* env,
                                           double value);

        static GM_ListValue* list_value (GM_Environment* env);

        static GM_PairValue* pair_value (GM_Environment* env,
                                         const std::string& key,
                                         GM_Value* value);

        static GM_DictValue* dict_value (GM_Environment* env);

        static GM_VarNameValue* var_name_value (GM_Environment* env,
                                                const std::string& var_name);

        static GM_CustomFuncValue* cust_func_value (GM_Environment* env,
                                                    const std::string& func_name,
                                                    const size_t& param_count,
                                                    const std::vector<std::string>* param_list,
                                                    GM_AST_TREE* func_body);

    };

}
