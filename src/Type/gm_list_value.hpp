#pragma once

#include <vector>

#include "../GM.h"
#include "gm_value.hpp"
#include "gm_types.h"

namespace GM
{
    class GM_Value;

    class GM_ListValue : extends(GM_Value)
    {

    public:
        GM_ListValue () { m_items = new std::vector<GM_Value*>(); }
        virtual ~GM_ListValue ();

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_LIST_VALUE;
        }

        void add_item(GM_Value* value);

        size_t get_item_count() const;

        GM_Value* operator[] (int index) const;

    protected:
        std::vector<GM_Value*>* m_items;

    };

}
