#pragma once

#include "gm_object.hpp"
#include "../Common/gm_errors.hpp"
#include "../Common/gm_utils.hpp"

#include <cstdint>
#include <cinttypes>

#define extends(class_name) public class_name
#define implements(class_name) public class_name


// --------------- Common conversion --------------- //
#define GM_SOURCE_FILE_SUFFIX ".gm"
#define GM_INTERPRETER_RUN_FLAG "__GM__INTERPRETER_RUN_FLAG__"
#define GM_INTERPRETER_PATH "GMPATH"

#define GM_INTERPRETER_REPL_MODE 0
#define GM_INTERPRETER_FILE_MODE 1

#define GM_AST_VARIADIC_PARAMS_FLAG SIZE_MAX

#define GM_DEFAULT_MEMORY_CHUNK_SIZE 4096


// --------------- Function Key Define --------------- //

#define FUNC_ADD_OP_KEY "__add__"
#define FUNC_SUB_OP_KEY "__sub__"
#define FUNC_MUL_OP_KEY "__mul__"
#define FUNC_DIV_OP_KEY "__div__"
#define FUNC_SET_OP_KEY "__set__"
#define FUNC_GET_OP_KEY "__get__"
#define FUNC_LS_OP_KEY  "__ls__"
#define FUNC_EQ_OP_KEY  "__eq__"
#define FUNC_GT_OP_KEY  "__gt__"
#define FUNC_LE_OP_KEY  "__le__"
#define FUNC_GE_OP_KEY  "__ge__"
#define FUNC_NE_OP_KEY  "__ne__"

#define BUILTIN_FUNC_PRINT  "print"
#define BUILTIN_FUNC_EXIT   "exit"
#define BUILTIN_FUNC_LET    "let"
#define BUILTIN_FUNC_FOR    "for"
#define BUILTIN_FUNC_DEF    "def"
#define BUILTIN_FUNC_IF     "if"
#define BUILTIN_FUNC_LS     "<"
#define BUILTIN_FUNC_EQ     "="
#define BUILTIN_FUNC_GT     ">"
#define BUILTIN_FUNC_LE     "<="
#define BUILTIN_FUNC_GE     ">="
#define BUILTIN_FUNC_NE     "!="
#define BUILTIN_FUNC_PAIR   ":"
#define BUILTIN_FUNC_LOAD   "import"
#define BUILTIN_FUNC_SET    "set"
#define BUILTIN_FUNC_GET    "get"


// --------------- Common Macro --------------- //

#define GM_STATIC_FUNCTION_D(func_name) \
static GM_Value* (func_name)(const GM_Parameter* param)

#define GM_FUNCTION_D(func_name) \
GM_Value* (func_name)(const GM_Parameter* param)

#define GM_FUNCTION_I(class_name, func_name) \
GM_Value* class_name::func_name(const GM_Parameter* param)

#define GM_VALUE_SET_FUNCTION(env, func_name, param_count, func) \
GM_Value::set_func(GM_Function::create_func(env, \
                                            func_name, \
                                            param_count, \
                                            func))

#define GM_VALUE_SET_GLOBAL_FUNCTION(func_name, param_count, func) \
GM_Value::set_func(GM_Function::create_func(GM_Interpreter::instance()->get_global_env(), \
                                            func_name, \
                                            param_count, \
                                            func))

#define GM_VALUE_SET_SELF_FUNCTION(func_name, param_count, func) \
GM_Value::set_func(GM_Function::create_func(get_environment(), \
                                            func_name, \
                                            param_count, \
                                            func))

#define GM_ENV_SET_FUNCTION(func_name, param_count, func) \
env->set_var(func_name, GM_Function::create_func(env, \
                                                 func_name, \
                                                 param_count, \
                                                 func))

#define GM_ENV_GET_FUNCTION(env, func_name) \
env->get_current_env_var(func_name)

#define GM_ENV_ALIAS_FUNCTION(func_name, origin_func_name, param_count, func) \
env->set_var(func_name, GM_Function::create_func(env, \
                                                 func_name, \
                                                 param_count, \
                                                 func))

// ----- get param without check ----- //
#define GET_PARAM_WITHOUT_CHECK(var_name, type, index) \
type* var_name = nullptr; \
if (index < param->get_list_param_count()) \
{ var_name = param->get_param<type>(index); }

#define GET_AST_TREE_WITHOUT_CHECK(var_name, index) GET_PARAM_WITHOUT_CHECK(var_name, GM_AST_TREE, index)

// ----- get param with check nullptr ----- //
#define GET_PARAM(var_name, type, index) \
auto var_name = param->get_param<type>(index); \
if (var_name == nullptr) \
{ \
    PRINT_ERROR_F("GetParamError: param(%d) type not mathcing type(%s) or value is nullptr", index, #type); \
    return GM_Value::null_value(); \
}

#define GET_VALUE_PARAM(var_name, index) GET_PARAM(var_name, GM_Value, index)
#define GET_AST_TREE(var_name, index) GET_PARAM(var_name, GM_AST_TREE, index)

// ----- get func with check nullptr ----- //
#define GET_FUNC(var_name, value, func_name) \
auto var_name = value->get_func(func_name); \
if (var_name == nullptr) \
{ \
    PRINT_ERROR_F("GetFuncError: func(%s) not found", func_name); \
    return GM_Value::null_value(); \
}

#define GET_CUR_ENV_FUNC(var_name, value, func_name) \
auto var_name = value->get_cur_env_func(func_name); \
if (var_name == nullptr) \
{ \
    PRINT_ERROR_F("GetFuncError: func(%s) not found", func_name); \
    return GM_Value::null_value(); \
}

#define GM_STR(format, ...) \
GM::GM_Utils::format_str(format, ##__VA_ARGS__)

#define GM_STR_FUNC(format, ...) \
std::string str() const override { return GM_STR(format, ##__VA_ARGS__); }

#ifdef DEBUG
    #define GM_AST_STR_FUNC(type) \
    GM_STR_FUNC("[$%s, token:%s, child_count:%zu]", #type, m_token.c_str(), get_child_count())
#else
    #define GM_AST_STR_FUNC(type)
#endif

#ifdef DEBUG
    #define GM_VALUE_DEBUG_STR_FUNC(type) \
    GM_STR_FUNC("<type: $%s, value: %s>", #type, _str().c_str())

    #define GM_VALUE_STR_FUNC(type)
#else
    #define GM_VALUE_DEBUG_STR_FUNC(type)

    #define GM_VALUE_STR_FUNC(type) \
    GM_STR_FUNC("%s", _str().c_str())
#endif

namespace GM
{
    
    class GM_Value;
    class GM_Parameter;
    
    typedef GM_Value* (*GM_FUNCTION_PTR)(const GM_Parameter*);
    
    static inline GM_Object* GM_Obj_Nullptr = nullptr;
    static inline GM_Value* GM_Value_Nullptr = nullptr;

}
