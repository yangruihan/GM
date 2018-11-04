#pragma once

#include <string>

#include "../gm_common_header.h"
#include "gm_list_value.hpp"

namespace GM
{
    class GM_Value;
    class GM_DictionaryValue;
    
    class GM_Parameter : extends(GM_Object)
    {
    public:
        GM_Parameter(const size_t count, ...);
        virtual ~GM_Parameter();
    
    public:
        template<typename T>
        T* get_param(const size_t index)
        {
            if (m_list_params == nullptr)
            {
                PRINT_ERROR("GetparamError: no param in param list");
                return nullptr;
            }
            
            if (index >= m_list_params->get_item_count())
            {
                PRINT_ERROR_F("GetparamError: index(%ld) out of range(%ld)",
                              index,
                              m_list_params->get_item_count());
                return nullptr;
            }
            
            auto param = (*m_list_params)[index];
            
            if (!GM_Utils::is_instance_of<GM_Value, T>(param))
            {
                PRINT_ERROR("GetparamError: param type is not match");
            }
            
            return dynamic_cast<T*>(param);
        }
        
        template<typename T>
        T* get_param(const std::string key)
        {
            return nullptr;
        }
        
    private:
        std::string* _handle_param_item(GM_Value* value) const;
        
    protected:
        GM_ListValue* m_list_params;
        GM_DictionaryValue* m_dict_params;

    };
 
}
