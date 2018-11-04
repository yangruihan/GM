#include "gm_parameter.hpp"

#include <cstdarg>

#include "../Common/gm_utils.hpp"
#include "gm_types_header.h"

namespace GM
{
 
    GM_Parameter::GM_Parameter(const size_t count, ...)
    {
        m_list_params = new std::vector<GM_Value*>();
        m_dict_params = new std::map<std::string, GM_Value*>();
        
        va_list args;
        va_start(args, count);
        for (size_t i = 0; i < count; i++)
        {
            auto value = va_arg(args, GM_Value*);
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

    GM_Parameter::GM_Parameter(std::vector<GM_Value*>* list_param,
                               std::map<std::string, GM_Value*>* dict_param)
                               : m_list_params(list_param),
                                 m_dict_params(dict_param)
    {}
    
    GM_Parameter::~GM_Parameter()
    {
        if (m_list_params != nullptr)
            delete m_list_params;

        if (m_dict_params != nullptr)
            delete m_dict_params;
    }
    
    std::string* GM_Parameter::_handle_param_item(GM::GM_Value *value) const
    {
        if (value == nullptr)
        {
            PRINT_ERROR("NullptrError: handle param failed, param is nullptr");
            return nullptr;
        }
        
        return nullptr;
    }

}
