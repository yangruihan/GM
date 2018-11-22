#include "gm_parameter.hpp"

#include <cstdarg>

#include "GM.h"

namespace GM
{
 
    GM_Parameter::GM_Parameter(GM_Environment* env,
                               const size_t count, ...): m_environment(env)
    {
        m_list_params = new std::vector<GM_Object*>();
        m_dict_params = new std::map<std::string, GM_Object*>();
        
        va_list args;
        va_start(args, count);
        for (size_t i = 0; i < count; i++)
        {
            auto value = va_arg(args, GM_Object*);
            auto dict_key = _handle_param_item(value);
            if (dict_key == nullptr)
            {
                m_list_params->push_back(value);
            }
            else
            {
                (*m_dict_params)[*dict_key] = value;
            }
        }
        va_end(args);
    }

    GM_Parameter::GM_Parameter(GM_Environment* env,
                               std::vector<GM_Object*>* list_param,
                               std::map<std::string, GM_Object*>* dict_param)
                               : m_environment(env),
                                 m_list_params(list_param),
                                 m_dict_params(dict_param)
    {}
    
    GM_Parameter::~GM_Parameter()
    {
        delete m_list_params;
        delete m_dict_params;
    }

    std::string GM_Parameter::str() const
    {
        return GM_Utils::format_str("[$GM_Parameter\n\tlist_params:%s\n\tdict_params:%s]",
                                    GM_Utils::vector_str(m_list_params).c_str(),
                                    GM_Utils::dict_str(m_dict_params).c_str());
    }
    
    std::string* GM_Parameter::_handle_param_item(GM::GM_Object *value) const
    {
        if (value == nullptr)
        {
            PRINT_ERROR("NullptrError: handle param failed, param is nullptr");
            return nullptr;
        }
        
        return nullptr;
    }

}
