#include "gm_builtin_func.hpp"
#include "GM.h"

#include <iostream>

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
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_IF,    3, GM_BuiltinFunc::__if);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_PAIR,  2, GM_BuiltinFunc::__pair);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_LOAD,  1, GM_BuiltinFunc::__import);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_GET,   2, GM_BuiltinFunc::__get);
        GM_ENV_SET_FUNCTION(BUILTIN_FUNC_SET,   3, GM_BuiltinFunc::__set);

        return true;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __print)
    {
        GET_AST_TREE(ast_tree, 0);

        auto value = ast_tree->eval();
        if (value == nullptr)
        {
            std::cout << "nullptr" << std::endl;
            return GM_Value::null_value();
        }

        GCINC(value);
        auto str = value->str();
        GCFREE(value);
        std::cout << str << std::endl;
        return GM_Value::null_value();
    }
    
    GM_FUNCTION_I(GM_BuiltinFunc, __exit)
    {
        const auto ret = (GM_BoolValue*) param->get_environment()->get_var(GM_INTERPRETER_RUN_FLAG);
        ret->set_value(false);
        return GM_Value::null_value();
    }
    
    GM_FUNCTION_I(GM_BuiltinFunc, __let)
    {
        GET_PARAM(ast_tree1, GM_AST_VAR_EXPR, 0);
        GET_AST_TREE(ast_tree2, 1);

        const auto var_key = ast_tree1->get_var_name_value();
        GM_Value* var_value = nullptr;

        auto value_var_expr = dynamic_cast<GM_AST_VAR_EXPR*>(ast_tree2);
        if (value_var_expr != nullptr && value_var_expr->get_token_index() != 0)
            var_value = value_var_expr->get_value();
        else
            var_value = ast_tree2->eval();

        if (var_key != nullptr && var_value != nullptr)
        {
            param->get_environment()->set_var(var_key->get_var_name(),
                                              var_value);
        }

        return GM_Value::null_value();
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __for)
    {
        GET_AST_TREE(ast_init_part,      0);
        GET_AST_TREE(ast_condition_part, 1);
        GET_AST_TREE(ast_change_part,    2);
        GET_AST_TREE(ast_statement_part, 3);

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

        return GM_Utils::get_last_value(ret);
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __ls)
    {
        GET_AST_TREE(ast_tree1, 0);
        GET_AST_TREE(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());
        GCINC(arg1);
        GCINC(arg2);

        GET_CUR_ENV_FUNC(func, arg1, FUNC_LS_OP_KEY);

        auto new_param = GM_GC::alloc_args<GM_Parameter>(param->get_environment(), 2, arg1, arg2);
        GCINC(new_param);

        const auto ret = func->eval(new_param);

        GCFREE(new_param);
        GCFREE(arg1);
        GCFREE(arg2);
        return ret;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __eq)
    {
        GET_AST_TREE(ast_tree1, 0);
        GET_AST_TREE(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());
        GCINC(arg1);
        GCINC(arg2);

        GET_CUR_ENV_FUNC(func, arg1, FUNC_EQ_OP_KEY);

        auto new_param = GM_GC::alloc_args<GM_Parameter>(param->get_environment(), 2, arg1, arg2);
        GCINC(new_param);

        const auto ret = func->eval(new_param);

        GCFREE(new_param);
        GCFREE(arg1);
        GCFREE(arg2);
        return ret;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __gt)
    {
        GET_AST_TREE(ast_tree1, 0);
        GET_AST_TREE(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());
        GCINC(arg1);
        GCINC(arg2);

        GET_CUR_ENV_FUNC(func, arg1, FUNC_GT_OP_KEY);

        auto new_param = GM_GC::alloc_args<GM_Parameter>(param->get_environment(), 2, arg1, arg2);
        GCINC(new_param);

        const auto ret = func->eval(new_param);

        GCFREE(new_param);
        GCFREE(arg1);
        GCFREE(arg2);
        return ret;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __le)
    {
        GET_AST_TREE(ast_tree1, 0);
        GET_AST_TREE(ast_tree2, 1);

        auto arg1 = dynamic_cast<GM_Value*>(ast_tree1->eval());
        auto arg2 = dynamic_cast<GM_Value*>(ast_tree2->eval());
        GCINC(arg1);
        GCINC(arg2);

        GET_CUR_ENV_FUNC(func, arg1, FUNC_LE_OP_KEY);

        auto new_param = GM_GC::alloc_args<GM_Parameter>(param->get_environment(), 2, arg1, arg2);
        GCINC(new_param);

        const auto ret = func->eval(new_param);

        GCFREE(new_param);
        GCFREE(arg1);
        GCFREE(arg2);
        return ret;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __ge)
    {
        GET_AST_TREE(ast_tree1, 0);
        GET_AST_TREE(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());
        GCINC(arg1);
        GCINC(arg2);

        GET_CUR_ENV_FUNC(func, arg1, FUNC_GE_OP_KEY);

        auto new_param = GM_GC::alloc_args<GM_Parameter>(param->get_environment(), 2, arg1, arg2);
        GCINC(new_param);

        const auto ret = func->eval(new_param);

        GCFREE(new_param);
        GCFREE(arg1);
        GCFREE(arg2);
        return ret;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __ne)
    {
        GET_AST_TREE(ast_tree1, 0);
        GET_AST_TREE(ast_tree2, 1);

        auto arg1 = GM_Value::convert_to_value(ast_tree1->eval());
        auto arg2 = GM_Value::convert_to_value(ast_tree2->eval());
        GCINC(arg1);
        GCINC(arg2);

        GET_CUR_ENV_FUNC(func, arg1, FUNC_NE_OP_KEY);

        auto new_param = GM_GC::alloc_args<GM_Parameter>(param->get_environment(), 2, arg1, arg2);
        GCINC(new_param);

        const auto ret = func->eval(new_param);

        GCFREE(new_param);
        GCFREE(arg1);
        GCFREE(arg2);
        return ret;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __def)
    {
        GET_PARAM(func_name_part, GM_AST_VAR_EXPR,   0);
        GET_PARAM(param_list_part, GM_AST_LIST_EXPR, 1);
        GET_AST_TREE(func_body_part, 2);

        auto func_name = func_name_part->get_token();
        if (!GM_CustomFuncValue::check_func_name_valid(func_name))
        {
            PRINT_ERROR_F("SyntaxError: function name(%s) is invalid", func_name.c_str());
            return GM_Value::null_value();
        }

        auto count = param_list_part->get_child_count();
        auto param_names = new std::vector<std::string>(count);
        for (size_t i = 0; i < count; i++)
        {
            auto child = param_list_part->get_child(i);
            if (!GM_Utils::is_instance_of<GM_AST_TREE, GM_AST_VAR_EXPR>(child))
            {
                PRINT_ERROR("SyntaxError: function parameter part error");
                return GM_Value::null_value();
            }

            (*param_names)[i] = child->get_token();
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

    GM_FUNCTION_I(GM_BuiltinFunc, __if)
    {
        GET_AST_TREE(ast_condition_part,            0);
        GET_AST_TREE_WITHOUT_CHECK(ast_true_part,  1);
        GET_AST_TREE_WITHOUT_CHECK(ast_false_part, 2);

        auto condition_result = dynamic_cast<GM_BoolValue*>(ast_condition_part->eval());
        if (condition_result == nullptr)
        {
            PRINT_ERROR("SyntaxError: condition statement not return a bool value");
            return GM_Value::null_value();
        }
        GCINC(condition_result);

        GM_Value* ret = GM_Value::null_value();
        if (condition_result->get_value())
        {
            ret = ast_true_part->eval();
        }
        else
        {
            if (ast_false_part != nullptr)
                ret = ast_false_part->eval();
        }

        GCFREE(condition_result);

        return GM_Utils::get_last_value(ret);
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __pair)
    {
        GET_PARAM(ast_key, GM_AST_STR_LITERAL_EXPR, 0);
        GET_AST_TREE(ast_value, 1);

        auto key_value = dynamic_cast<GM_StrValue*>(ast_key->eval());
        if (key_value == nullptr)
        {
            PRINT_ERROR("SyntaxError: key statement not return a str value");
            return GM_Value::null_value();
        }

        GM_Value* var_value = nullptr;

        auto value_var_expr = dynamic_cast<GM_AST_VAR_EXPR*>(ast_value);
        if (value_var_expr != nullptr && value_var_expr->get_token_index() != 0)
            var_value = value_var_expr->get_value();
        else
            var_value = ast_value->eval();

        if (var_value == nullptr)
        {
            PRINT_ERROR("SyntaxError: value statement not return a value");
            return GM_Value::null_value();
        }

        return GM_Value::pair_value(param->get_environment(),
                                    key_value->get_value(),
                                    var_value);
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __import)
    {
        GET_PARAM(ast_tree, GM_AST_STR_LITERAL_EXPR, 0);

        auto str_value = dynamic_cast<GM_StrValue*>(ast_tree->eval());
        if (str_value == nullptr)
        {
            PRINT_ERROR("SyntaxError: file path statement not return a str value");
            return GM_Value::null_value();
        }

        auto ret = GM_Interpreter::instance()->parse_file(str_value->get_value());

        return GM_Value::bool_value(param->get_environment(), ret == 0);
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __get)
    {
        GET_PARAM(container_node, GM_AST_VAR_EXPR,         0);
        GET_PARAM(index_node, GM_AST_NUMBER_LITERAL_EXPR, 1);

        if (index_node->is_float())
        {
            PRINT_ERROR_F("IndexError: index(%s) must be an integer",
                          index_node->str().c_str());
            return GM_Value::null_value();
        }

        auto container = GM_Value::convert_to_value(container_node->eval());
        auto index = GM_Value::convert_to_value(index_node->eval());
        GCINC(container);
        GCINC(index);

        GET_CUR_ENV_FUNC(func, container, FUNC_GET_OP_KEY);

        auto new_param = GM_GC::alloc_args<GM_Parameter>(param->get_environment(),
                                          2, container, index);
        GCINC(new_param);

        const auto ret = func->eval(new_param);

        GCFREE(new_param);
        GCFREE(container);
        GCFREE(index);

        return ret;
    }

    GM_FUNCTION_I(GM_BuiltinFunc, __set)
    {
        GET_PARAM(container_node, GM_AST_VAR_EXPR,         0);
        GET_PARAM(index_node, GM_AST_NUMBER_LITERAL_EXPR, 1);
        GET_AST_TREE(value_node, 2);

        if (index_node->is_float())
        {
            PRINT_ERROR_F("IndexError: index(%s) must be an integer",
                          index_node->str().c_str());
            return GM_Value::null_value();
        }

        auto container = GM_Value::convert_to_value(container_node->eval());
        auto index = GM_Value::convert_to_value(index_node->eval());
        auto value = value_node->eval();
        GCINC(container);
        GCINC(index);
        GCINC(value);

        GET_CUR_ENV_FUNC(func, container, FUNC_SET_OP_KEY);

        auto new_param = GM_GC::alloc_args<GM_Parameter>(param->get_environment(),
                                                     3, container, index, value);
        GCINC(new_param);
        const auto ret = func->eval(new_param);

        GCFREE(new_param);
        GCFREE(container);
        GCFREE(index);
        GCFREE(value);

        return ret;
    }

}
