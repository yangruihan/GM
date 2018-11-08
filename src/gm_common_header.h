#pragma once

#include "gm_object.hpp"
#include "Common/gm_errors.hpp"
#include "Common/gm_utils.hpp"

#include <cstdint>

#define GM_SOURCE_FILE_SUFFIX ".gm"

#define extends(class_name) public class_name
#define implements(class_name) public class_name

#define GM_AST_VARIADIC_PARAMS_FLAG SIZE_MAX

#define GM_INTERPRETER_RUN_FLAG "__GM__INTERPRETER_RUN_FLAG__"
#define GM_INTERPRETER_PATH "GMPATH"

#define GM_INTERPRETER_REPL_MODE 0
#define GM_INTERPRETER_FILE_MODE 1

#define FUNC_ADD_OP_KEY "__add"
#define FUNC_SUB_OP_KEY "__sub"
#define FUNC_MUL_OP_KEY "__mul"
#define FUNC_DIV_OP_KEY "__div"
#define FUNC_LS_OP_KEY  "__ls"
#define FUNC_EQ_OP_KEY  "__eq"
#define FUNC_GT_OP_KEY  "__gt"
#define FUNC_LE_OP_KEY  "__le"
#define FUNC_GE_OP_KEY  "__ge"
#define FUNC_NE_OP_KEY  "__ne"

#define GM_STATIC_FUNCTION_D(func_name) \
static GM_Value* (func_name)(const GM_Parameter* param)

#define GM_FUNCTION_D(func_name) \
GM_Value* (func_name)(const GM_Parameter* param)

#define GM_FUNCTION_I(class_name, func_name) \
GM_Value* class_name::func_name(const GM_Parameter* param)

#define GM_VALUE_SET_FUNCTION(func_name, param_count, func) \
GM_Value::set_func(GM_Function::create_func(func_name, \
                                            param_count, \
                                            func))

#define GM_ENV_SET_FUNCTION(func_name, param_count, func) \
env->set_var(func_name, GM_Function::create_func(func_name, \
                                                 param_count, \
                                                 func))

#define GM_ENV_ALIAS_FUNCTION(func_name, origin_func_name, param_count, func) \
env->set_var(func_name, GM_Function::create_func(func_name, \
                                                 param_count, \
                                                 func))

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
#define GM_VALUE_STR_FUNC(type) \
GM_STR_FUNC("[$%s, value:%s]", #type, _str().c_str())
#else
#define GM_VALUE_STR_FUNC(type) \
GM_STR_FUNC("%s", _str().c_str())
#endif

namespace GM
{
    
    class GM_Value;
    class GM_Parameter;
    
    typedef GM_Value* (*GM_FUNCTION_PTR)(const GM_Parameter*);
    
}
