#pragma once

#include <string>
#include <vector>
#include <map>

#include "../gm_common_header.h"

namespace GM
{
    class GM_Value;
    
    class GM_Parameter : extends(GM_Object)
    {
    public:
        GM_Parameter(const size_t count, ...);
        GM_Parameter(std::vector<GM_Value*>* list_param,
                     std::map<std::string, GM_Value*>* dict_param);
        virtual ~GM_Parameter();
    
    public:
        template<typename T>
        T* get_param(const size_t index) const
        {
            if (m_list_params == nullptr)
            {
                PRINT_ERROR("GetparamError: no param in param list");
                return nullptr;
            }
            
            if (index >= m_list_params->size())
            {
                PRINT_ERROR_F("GetparamError: index(%ld) out of range(%ld)",
                              index,
                              m_list_params->size());
                return nullptr;
            }
            
            auto ret = GM_Utils::is_instance_of<GM_Value, T>((*m_list_params)[index]);
            
            if (ret == nullptr)
            {
                PRINT_ERROR("GetparamError: param type is not match");
            }
            
            return ret;
        }
        
        template<typename T>
        T* get_param(const std::string key) const
        {
            if (m_dict_params == nullptr)
            {
                PRINT_ERROR("GetparamError: no param in param dict");
                return nullptr;
            }
            
            auto it = m_dict_params->find(key);
            if (it == m_dict_params->end())
            {
                PRINT_ERROR_F("GetparamError: index(%ld) out of range(%ld)",
                              index,
                              m_list_params->size());
                return nullptr;
            }
            
            auto ret = GM_Utils::is_instance_of<GM_Value, T>(it->second);
            
            if (ret == nullptr)
            {
                PRINT_ERROR("GetparamError: param type is not match");
            }
            
            return ret;
        }
        
    private:
        std::string* _handle_param_item(GM_Value* value) const;
        
    protected:
        std::vector<GM_Value*>* m_list_params;
        std::map<std::string, GM_Value*>* m_dict_params;

    };
 
}
