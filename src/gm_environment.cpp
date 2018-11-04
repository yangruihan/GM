#include "gm_environment.hpp"
#include "GM.h"

namespace GM
{

    GM_Environment::GM_Environment ()
    {
        m_var_map = new std::map<std::string, GM_Value*>();
        m_func_map = new std::map<std::string, GM_Function*>();
    }
    
    GM_Environment::GM_Environment (const GM_Environment& other)
    {
        set_parent(&other);
    }
        
    GM_Environment::~GM_Environment ()
    {
        delete m_var_map;
        delete m_func_map;
    }
    
    void GM_Environment::set_value(std::string &var_name, GM::GM_Value *value)
    {
        if (value == nullptr)
        {
            PRINT_ERROR("NullptrError: set value failed, value is nullptr");
            return;
        }
        
        (*m_var_map)[var_name] = value;
    }
    
    GM::GM_Value *GM_Environment::get_value(std::string &var_name) const
    {
        auto it = m_var_map->find(var_name);
        if (it != m_var_map->end())
        {
            return it->second;
        }
        else
        {
            if (m_parent != nullptr)
                return m_parent->get_value(var_name);
            
            return nullptr;
        }
    }
    
    void GM_Environment::set_func(std::string &func_name, GM::GM_Function *func) {
        if (func == nullptr)
        {
            PRINT_ERROR("NullptrError: set func failed, func is nullptr");
            return;
        }
    }
    
    GM::GM_Function *GM_Environment::get_func(std::string &func_name) const
    {
        auto it = m_func_map->find(func_name);
        if (it != m_func_map->end())
        {
            return it->second;
        }
        
        return nullptr;
    }
    
}
