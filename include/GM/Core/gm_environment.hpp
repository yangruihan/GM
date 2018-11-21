#pragma once

#include <map>

#include "gm_common_header.h"

namespace GM
{
    class GM_Object;

    class GM_Environment : extends(GM_Object)
    {
    public:
        GM_Environment ();
        GM_Environment (GM_Environment* parent);
        ~GM_Environment () override;
        
        GM_Environment& operator=(const GM_Environment& other) = delete;

        static GM_Environment* create(GM_Environment* parent);

        std::string str() const override;
        
        void set_var(const std::string& var_name, GM_Value* var);
        GM_Value* get_var(const std::string& var_name,
                           const bool& find_loaded_env=true) const;
        GM_Value* get_current_env_var(const std::string& var_name) const;
        
        void set_parent(const GM_Environment* env) { m_parent = env; }
        const GM_Environment* get_parent() const { return m_parent; }
        
    protected:
        std::map<std::string, GM_Value*>* m_var_map;
        
        const GM_Environment* m_parent;
    };

}
