#include "gm_builtin_func.hpp"
#include "GM.h"

#include <iostream>

#define get_param(var_name, type, index) \
auto var_name = param->get_param<type>(index); \
if (var_name == nullptr) \
{ \
    PRINT_ERROR_F("GetParamError: param(%d) type not mathcing type(%s) or value is nullptr", index, #type); \
    return GM_Value::null_value(); \
}

#define get_ast_tree(var_name, index) get_param(var_name, GM_AST_TREE, index)

#define get_func(var_name, value, func_name) \
auto var_name = value->get_func(func_name); \
if (var_name == nullptr) \
{ \
    PRINT_ERROR_F("GetFuncError: func(%s) not found", func_name); \
    return GM_Value::null_value(); \
}

namespace GM
{

    bool GM_BuiltinFunc::init(GM_Environment* env)
    {
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_PRINT, 1, GM_BuiltinFunc::__print);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_EXIT,  0, GM_BuiltinFunc::__exit);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_LET,   2, GM_BuiltinFunc::__let);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_FOR,   4, GM_BuiltinFunc::__for);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_LS,    2, GM_BuiltinFunc::__ls);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_EQ,    2, GM_BuiltinFunc::__eq);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_GT,    2, GM_BuiltinFunc::__gt);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_LE,    2, GM_BuiltinFunc::__le);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_GE,    2, GM_BuiltinFunc::__ge);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_NE,    2, GM_BuiltinFunc::__ne);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_DEF,   3, GM_BuiltinFunc::__def);

        return true;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __print)
    {
        get_ast_tree(ast_tree, 0);

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
    
    GM_FUNCTION_I(GM_BuiltinFunc, __exit)
    {
        auto ret = GM_Value::bool_value(param->get_environment(), false);
        param->get_environment()->set_var(GM_INTERPRETER_RUN_FLAG,
                                          ret);
        return ret;
    }
    
    GM_FUNCTION_I(GM_BuiltinFunc, __let)
    {
        get_param(ast_tree1, GM_AST_VAR_EXPR, 0);
        get_ast_tree(ast_tree2, 1);

        auto var_key = ast_tree1->get_var_name_value();
        auto var_value = ast_tree2->eval();

        if (var_key != nullptr && var_value != nullptr)
        {
            param->get_environment()->set_var(var_key->get_var_name(),
                                              var_value);
        }
        return var_value;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __for)
    {
        get_ast_tree(ast_init_part,      0);
        get_ast_tree(ast_condition_part, 1);
        get_ast_tree(ast_change_part,    2);
        get_ast_tree(ast_statement_part, 3);

        // init
        ast_init_part->eval();

        auto condition_result = dynamic_cast<GM_BoolValue*>(ast_condition_part->eval());
        if (condition_result == nullptr)
        {
            PRINT_ERROR("SyntaxError: condition statement not return a bool value");
            return GM_Value::null_value();
        }

        GM_Value* ret;
        while (condition_result->get_value())
        {
            ret = ast_statement_part->eval();
            ast_change_part->eval();

            condition_result = dynamic_cast<GM_BoolValue*>(ast_condition_part->eval());
        }

        auto list_value = dynamic_cast<GM_ListValue*>(ret);
        if (list_value == nullptr)
            return ret;

      return (*list_value)[list_value->get_item_count() - 1];
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __ls)
    {
        get_ast_tree(ast_tree1, 0);
        get_ast_tree(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());

        get_func(func, arg1, FUNC_LS_OP_KEY);

        return func->eval(new GM_Parameter(param->get_environment(),
                                           2, arg1, arg2));
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __eq)
    {
        get_ast_tree(ast_tree1, 0);
        get_ast_tree(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());

        get_func(func, arg1, FUNC_EQ_OP_KEY);

        return func->eval(new GM_Parameter(param->get_environment(),
                                           2, arg1, arg2));
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __gt)
    {
        get_ast_tree(ast_tree1, 0);
        get_ast_tree(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());

        get_func(func, arg1, FUNC_GT_OP_KEY);

        return func->eval(new GM_Parameter(param->get_environment(),
                                           2, arg1, arg2));
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __le)
    {
        get_ast_tree(ast_tree1, 0);
        get_ast_tree(ast_tree2, 1);

        auto arg1 = dynamic_cast<GM_Value*>(ast_tree1->eval());
        auto arg2 = dynamic_cast<GM_Value*>(ast_tree2->eval());

        get_func(func, arg1, FUNC_LE_OP_KEY);

        return func->eval(new GM_Parameter(param->get_environment(),
                                           2, arg1, arg2));
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __ge)
    {
        get_ast_tree(ast_tree1, 0);
        get_ast_tree(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());

        get_func(func, arg1, FUNC_GE_OP_KEY);

        return func->eval(new GM_Parameter(param->get_environment(),
                                           2, arg1, arg2));
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __ne)
    {
        get_ast_tree(ast_tree1, 0);
        get_ast_tree(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());

        get_func(func, arg1, FUNC_NE_OP_KEY);

        return func->eval(new GM_Parameter(param->get_environment(),
                                           2, arg1, arg2));
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __def)
    {
        get_param(func_name_part, GM_AST_VAR_EXPR,   0);
        get_param(param_list_part, GM_AST_LIST_EXPR, 1);
        get_ast_tree(func_body_part, 2);

        auto func_name = func_name_part->get_token();
        if (!GM_CustomFuncValue::check_func_name_valid(func_name))
        {
            PRINT_ERROR_F("SyntaxError: function name(%s) is invalid", func_name.c_str());
            return GM_Value::null_value();
        }

        std::vector<std::string>* param_names = new std::vector<std::string>();
        for (size_t i = 0, count = param_list_part->get_child_count(); i < count; i++)
        {
            auto child = param_list_part->get_child(i);
            if (!GM_Utils::is_instance_of<GM_AST_TREE, GM_AST_VAR_EXPR>(child))
            {
                PRINT_ERROR("SyntaxError: function parameter part error");
                return GM_Value::null_value();
            }

            param_names->push_back(child->get_token());
        }

        auto new_env = GM_Utils::set_env_for_childs(func_body_part, param->get_environment());

        auto cust_func_value = GM_Value::cust_func_value(new_env,
                                                         func_name,
                                                         param_list_part->get_child_count(),
                                                         param_names,
                                                         func_body_part);
        param->get_environment()->set_var(func_name, cust_func_value);
        return cust_func_value;
    }

}
