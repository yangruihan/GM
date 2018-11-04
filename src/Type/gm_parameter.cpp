#include "gm_parameter.hpp"

#include <cstdarg>

#include "../Common/gm_utils.hpp"
#include "gm_types_header.h"

namespace GM
{
 
    GM_Parameter::GM_Parameter(const size_t count, ...)
    {
        va_list args;
        va_start(args, count);
        for (size_t i = 0; i < count; i++)
        {
            auto value = va_arg(args, GM_Value*);
            auto dict_key = _handle_param_item(value);
            if (dict_key == nullptr)
            {
                if (m_list_params == nullptr)
                    m_list_params = new std::vector<GM_Value*>();
                
                m_list_params->push_back(value);
            }
            else
            {
            }
        }
    }
    
    GM_Parameter::~GM_Parameter() {}
    
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
