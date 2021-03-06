#include "gm_environment.hpp"
#include "GM.h"

namespace GM
{

    GM_Environment::GM_Environment (): m_parent(nullptr)
    {
        m_var_map = new std::map<std::string, GM_Value*>();
    }
    
    GM_Environment::GM_Environment (GM_Environment* parent): m_parent(parent)
    {
        m_var_map = new std::map<std::string, GM_Value*>();

        if (m_parent != nullptr)
            GCINC(m_parent);
    }
        
    GM_Environment::~GM_Environment ()
    {
        if (m_parent != nullptr)
            GCFREE(m_parent);

        delete m_var_map;
        m_var_map = nullptr;
    }

    std::string GM_Environment::str() const
    {
#ifdef DEBUG
        return GM_Utils::format_str("[<class '%s'>, refcnt: %" PRIu64 ", insidx: %" PRIu64 "]",
                                    "environment",
                                    GCREFCNF(this),
                                    GCINSIDX(this));
#else
        return "<class 'environment'>";
#endif
    }

    GM_Environment* GM_Environment::create(GM_Environment *parent)
    {
        return GM_GC::alloc_args<GM_Environment>(parent);
    }

    void GM_Environment::clear(GM_Environment* env)
    {
        for (auto & it : *env->m_var_map)
            GCFREE(it.second);
        env->m_var_map->clear();
    }
    
    void GM_Environment::set_var(const std::string& var_name, GM_Value *var)
    {
        if (var == nullptr)
        {
            PRINT_ERROR("NullptrError: set value failed, value is nullptr");
            return;
        }

        auto it = m_var_map->find(var_name);
        if (it != m_var_map->end())
            GCFREE((*m_var_map)[var_name]);

        GCINC(var);
        (*m_var_map)[var_name] = var;
    }
    
    GM_Value* GM_Environment::get_var(const std::string& var_name,
                                      const bool& find_loaded_env) const
    {
        if (var_name.empty())
            return nullptr;

        if (m_var_map == nullptr)
        {
            PRINT_ERROR("NullptrError: environment variable map is null");
            return nullptr;
        }

        const auto it = m_var_map->find(var_name);
        if (it != m_var_map->end())
        {
            return it->second;
        }
        else
        {
            if (m_parent != nullptr)
            {
                return m_parent->get_var(var_name);
            }
            else if (find_loaded_env)
            {
                const auto interpreter = GM_Interpreter::instance();
                if (interpreter == nullptr || !GCISVALID(interpreter))
                    return nullptr;
                
                return interpreter->get_var_from_loaded_env(var_name);
            }

            return nullptr;
        }
    }

    void GM_Environment::set_parent(GM_Environment* env)
    {
        if (m_parent == env)
            return;

        if (m_parent != nullptr)
            GCFREE(m_parent);

        GCINC(m_parent);
        m_parent = env;
    }

    GM_Value* GM_Environment::get_current_env_var(const std::string& var_name) const
    {
        const auto it = m_var_map->find(var_name);
        if (it != m_var_map->end())
            return it->second;
        else
            return nullptr;
    }

    GM_Value*& GM_Environment::get_current_env_var(const std::string& var_name)
    {
        const auto it = m_var_map->find(var_name);
        if (it != m_var_map->end())
            return it->second;
        else
            return GM_Value_Nullptr;
    }

}
