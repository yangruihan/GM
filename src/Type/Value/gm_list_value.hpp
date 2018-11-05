#pragma once

#include <vector>

#include "../../gm_common_header.h"
#include "../gm_value.hpp"
#include "../gm_types.h"

namespace GM
{
    class GM_Value;
    class GM_Environment;

    class GM_ListValue : extends(GM_Value)
    {

    public:
        GM_ListValue (GM_Environment* env);
        virtual ~GM_ListValue ();

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_LIST_VALUE;
        }

        std::string str() const override;

        GM_ListValue* add_item(GM_Value* value);

        size_t get_item_count() const;

        GM_Value* operator[] (int index) const;

    protected:
        void _init_functions() override;

    protected:
        std::vector<GM_Value*>* m_items;

    };

}
