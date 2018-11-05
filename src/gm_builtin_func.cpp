#include "gm_builtin_func.hpp"
#include "GM.h"

#include <iostream>

namespace GM
{

    bool GM_BuiltinFunc::init(GM_Environment* env)
    {
        env->set_var(BUILTIN_FUNC_PRINT, GM_Function::create_func(BUILTIN_FUNC_PRINT,
                                                                  1,
                                                                  GM_BuiltinFunc::__print));

        env->set_var(BUILTIN_FUNC_EXIT, GM_Function::create_func(BUILTIN_FUNC_EXIT,
                                                                 0,
                                                                 GM_BuiltinFunc::__exit));

        env->set_var(BUILTIN_FUNC_LET, GM_Function::create_func(BUILTIN_FUNC_LET,
                                                                2,
                                                                GM_BuiltinFunc::__let));

        return true;
    }

    GM_Value* GM_BuiltinFunc::__print(const GM_Parameter* param)
    {
        auto ast_tree = param->get_param<GM_AST_TREE>(0);
        if (ast_tree == nullptr)
        {
            std::cout << "nullptr" << std::endl;
            return GM_Value::null_value();
        }
        else
        {
            auto value = ast_tree->eval();
            if (value == nullptr)
            {
                std::cout << "nullptr" << std::endl;
                return GM_Value::null_value();
            }

            auto str = value->str();
            std::cout << str << std::endl;
            return GM_Value::str_value(param->get_environment(), str);
        }
    }
    
    GM_Value *GM_BuiltinFunc::__exit(const GM::GM_Parameter *param)
    {
        auto ret = GM_Value::bool_value(param->get_environment(), false);
        param->get_environment()->set_var(GM_INTERPRETER_RUN_FLAG,
                                          ret);
        return ret;
    }
    
    GM_Value *GM_BuiltinFunc::__let(const GM_Parameter *param)
    {
        auto ast_tree1 = param->get_param<GM_AST_VAR_EXPR>(0);
        auto ast_tree2 = param->get_param<GM_AST_TREE>(1);

        if (ast_tree1 == nullptr || ast_tree2 == nullptr)
        {
            PRINT_ERROR("ArgumentsError: type not match");
            return GM_Value::null_value();
        }

        auto var_key = dynamic_cast<GM_StrValue*>(ast_tree1->eval());
        auto var_value = ast_tree2->eval();

        if (var_key != nullptr && var_value != nullptr)
        {
            param->get_environment()->set_var(var_key->str(),
                                              var_value);
        }
        return var_value;
    }

}
