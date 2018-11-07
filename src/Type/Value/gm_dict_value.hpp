#pragma once

#include "../../gm_common_header.h"
#include "../gm_value.hpp"

#include <string>
#include <map>

namespace GM
{
    class GM_Value;
    class GM_Environment;
    class GM_PairValue;

    class GM_DictValue : extends(GM_Value)
    {

    public:
        GM_DictValue (GM_Environment* env);
        ~GM_DictValue () override;

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_DICT_VALUE;
        }
        
        std::string str() const override;

        GM_DictValue* add_item(const std::string& key,
                                     GM_PairValue* value);

        size_t get_item_count() const;

        GM_PairValue* operator[] (const std::string& key) const;
        
    protected:
        void _init_functions() override;

    protected:
        std::map<std::string, GM_PairValue*>* m_items;
        
    };

}
