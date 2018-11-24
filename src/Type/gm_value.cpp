#include "gm_value.hpp"
#include "gm_function.hpp"

#include "GM.h"

namespace GM
{

    GM_Value::GM_Value(GM_Environment* env): m_environment(env)
    {
//        DEBUG_LOG_F("** inc env ref cnt %" PRIu64 ", %" PRIu64, GM_GC::get_ref_cnt(m_environment), GM_GC::get_ins_idx(m_environment));
        GM_GC::inc_ref(m_environment);
    }

    GM_Value::~GM_Value()
    {
        GM_GC::free(m_environment);
        m_environment = nullptr;
//        DEBUG_LOG_F("** dec env ref cnt %" PRIu64 ", %" PRIu64, GM_GC::get_ref_cnt(m_environment), GM_GC::get_ins_idx(m_environment));
    }

    GM_Value* GM_Value::convert_to_value(GM_Object* obj)
    {
        auto var_name_value = dynamic_cast<GM_VarNameValue*>(obj);
        if (var_name_value == nullptr)
        {
            return dynamic_cast<GM_Value*>(obj);
        }

        auto var_obj = var_name_value->get_environment()->get_var(var_name_value->get_var_name());
        return dynamic_cast<GM_Value*>(var_obj);
    }

    GM_Function* GM_Value::get_func(const std::string& func_name) const
    {
        auto func = m_environment->get_var(func_name);
        if (func != nullptr)
            return dynamic_cast<GM_Function*>(func);

        return nullptr;
    }

    GM_Function* GM_Value::get_cur_env_func(const std::string &func_name) const
    {
        auto func = m_environment->get_current_env_var(func_name);
        if (func != nullptr)
            return dynamic_cast<GM_Function*>(func);

        return nullptr;
    }

    void GM_Value::set_func(GM_Function* func)
    {
        if (func == nullptr)
        {
            PRINT_ERROR("Nullptr Error: func is nullptr");
            return;
        }

        m_environment->set_var(func->get_name(), func);
    }

    /* ----- create value ----- */
    GM_NullValue* GM_Value::null_value()
    { return GM_NullValue::s_ins; }

    GM_BoolValue* GM_Value::bool_value(GM_Environment* env, const std::string &token)
    { return GM_GC::alloc_args<GM_BoolValue>(env, token); }

    GM_BoolValue* GM_Value::bool_value(GM_Environment* env, const bool &value)
    { return GM_GC::alloc_args<GM_BoolValue>(env, value); }

    GM_StrValue* GM_Value::str_value(GM_Environment *env, const std::string &token)
    { return GM_GC::alloc_args<GM_StrValue>(env, token); }

    GM_IntValue* GM_Value::int_value (GM_Environment* env,
                                      const std::string& token)
    { return GM_GC::alloc_args<GM_IntValue>(env, token); }

    GM_IntValue* GM_Value::int_value (GM_Environment* env,
                                      const int& value)
    { return GM_GC::alloc_args<GM_IntValue>(env, value); }

    GM_IntValue* GM_Value::int_value (GM_Environment* env,
                                      const double& value)
    { return GM_GC::alloc_args<GM_IntValue>(env, value); }

    GM_FloatValue* GM_Value::float_value (GM_Environment* env,
                                          const std::string& token)
    { return GM_GC::alloc_args<GM_FloatValue>(env, token); }

    GM_FloatValue* GM_Value::float_value (GM_Environment* env,
                                          int value)
    { return GM_GC::alloc_args<GM_FloatValue>(env, value); }

    GM_FloatValue* GM_Value::float_value (GM_Environment* env,
                                          double value)
    { return GM_GC::alloc_args<GM_FloatValue>(env, value); }

    GM_ListValue* GM_Value::list_value(GM_Environment *env)
    { return GM_GC::alloc_args<GM_ListValue>(env); }

    GM_PairValue* GM_Value::pair_value (GM_Environment* env,
                                        const std::string& key,
                                        GM_Value* value)
    { return GM_GC::alloc_args<GM_PairValue>(env, key, value); }

    GM_DictValue* GM_Value::dict_value(GM_Environment *env)
    { return GM_GC::alloc_args<GM_DictValue>(env); }

    GM_VarNameValue* GM_Value::var_name_value(GM_Environment *env, const std::string &var_name)
    { return GM_GC::alloc_args<GM_VarNameValue>(env, var_name); }

    GM_CustomFuncValue *GM_Value::cust_func_value(GM_Environment *env,
                                                  const std::string& func_name,
                                                  const size_t& param_count,
                                                  const std::vector<std::string>* param_list,
                                                  GM_AST_TREE *func_body)
    { return GM_GC::alloc_args<GM_CustomFuncValue>(env, func_name, param_count, param_list, func_body); }
}
