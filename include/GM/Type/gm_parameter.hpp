#pragma once

#include <string>
#include <vector>
#include <map>

#include "../Core/gm_common_header.h"

namespace GM
{
    class GM_Object;
    class GM_Environment;
    
    class GM_Parameter : extends(GM_Object)
    {
    public:
        GM_Parameter(GM_Environment* env,
                     const size_t count, ...);
        GM_Parameter(GM_Environment* env,
                     std::vector<GM_Object*>* list_param,
                     std::map<std::string, GM_Object*>* dict_param);
        virtual ~GM_Parameter();
    
    public:
        std::string str() const override;

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
                PRINT_ERROR_F("GetparamError: index(%zu) out of range(%zu)",
                              index,
                              m_list_params->size());
                return nullptr;
            }
            
            auto ret = GM_Utils::is_instance_of<GM_Object, T>((*m_list_params)[index]);
            
            if (ret == nullptr)
            {
                PRINT_ERROR("GetparamError: param type is not match");
            }
            
            return ret;
        }
        
        template<typename T>
        T* get_param(const std::string& key) const
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
            
            auto ret = GM_Utils::is_instance_of<GM_Object, T>(it->second);
            
            if (ret == nullptr)
            {
                PRINT_ERROR("GetparamError: param type is not match");
            }
            
            return ret;
        }

        GM_Environment* get_environment() const { return m_environment; }

        size_t get_list_param_count() const { return m_list_params->size(); }
        std::vector<GM_Object*>* get_list_params() const { return m_list_params; }

        size_t get_dict_param_count() const { return m_dict_params->size(); }
        std::map<std::string, GM_Object*>* get_dict_params() const { return m_dict_params; }

    private:
        std::string* _handle_param_item(GM_Object* value) const;
        
    protected:
        GM_Environment*                    m_environment;
        std::vector<GM_Object*>*           m_list_params;
        std::map<std::string, GM_Object*>* m_dict_params;
    };
 
}
