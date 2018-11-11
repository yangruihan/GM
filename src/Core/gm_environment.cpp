#include "gm_environment.hpp"
#include "GM.h"

namespace GM
{

    GM_Environment::GM_Environment ()
    {
        m_var_map = new std::map<std::string, GM_Value*>();
        set_parent(nullptr);
    }
    
    GM_Environment::GM_Environment (GM_Environment* parent)
    {
        m_var_map = new std::map<std::string, GM_Value*>();
        set_parent(parent);
    }
        
    GM_Environment::~GM_Environment ()
    {
        delete m_var_map;
    }

    GM_Environment* GM_Environment::create(GM_Environment *parent)
    {
        return new GM_Environment(parent);
    }
    
    void GM_Environment::set_var(const std::string& var_name, GM_Value *var)
    {
        if (var == nullptr)
        {
            PRINT_ERROR("NullptrError: set value failed, value is nullptr");
            return;
        }
        
        (*m_var_map)[var_name] = var;
    }
    
    GM_Value* GM_Environment::get_var(const std::string& var_name,
                                       const bool& find_loaded_env) const
    {
        if (var_name.size() == 0)
            return nullptr;

        auto it = m_var_map->find(var_name);
        if (it != m_var_map->end())
        {
            return it->second;
        }
        else
        {
            if (m_parent != nullptr)
                return m_parent->get_var(var_name);
            else if (find_loaded_env)
                return GM_Interpreter::instance()->get_var_from_loaded_env(var_name);

            return nullptr;
        }
    }

    GM_Value* GM_Environment::get_current_env_var(const std::string& var_name) const
    {
        auto it = m_var_map->find(var_name);
        if (it != m_var_map->end())
            return it->second;
        else
            return nullptr;
    }

}
