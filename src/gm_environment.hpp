#pragma once

#include <map>

#include "gm_common_header.h"

namespace GM
{
    class GM_Value;
    class GM_Function;

    class GM_Environment : extends(GM_Object)
    {
    public:
        GM_Environment ();
        GM_Environment (const GM_Environment& parent);
        ~GM_Environment () override;
        
        GM_Environment& operator=(const GM_Environment& other) = delete;
        
        void set_value(std::string& var_name, GM_Value* value);
        GM_Value* get_value(std::string& var_name) const;
        
        void set_func(std::string& func_name, GM_Function* func);
        GM_Function* get_func(std::string& func_name) const;
        
        void set_parent(const GM_Environment* env) { m_parent = env; }
        const GM_Environment* get_parent() const { return m_parent; }
        
    protected:
        std::map<std::string, GM_Value*>* m_var_map;
        std::map<std::string, GM_Function*>* m_func_map;
        
        const GM_Environment* m_parent;
    };

}
