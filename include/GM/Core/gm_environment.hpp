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
        explicit GM_Environment (GM_Environment* parent);
        ~GM_Environment () override;
        
        GM_Environment& operator=(const GM_Environment& other) = delete;

        static GM_Environment* create(GM_Environment* parent);
        static void clear(GM_Environment* env);

        std::string str() const override;
        
        void set_var(const std::string& var_name, GM_Value* var);
        
        GM_Value* get_var(const std::string& var_name,
                          const bool& find_loaded_env=true) const;

        GM_Value* get_current_env_var(const std::string& var_name) const;
        GM_Value*& get_current_env_var(const std::string& var_name);
        
        void set_parent(GM_Environment* env);
        const GM_Environment* get_parent() const { return m_parent; }
        
    protected:
        std::map<std::string, GM_Value*>* m_var_map;
        
        GM_Environment* m_parent;
    };

}
