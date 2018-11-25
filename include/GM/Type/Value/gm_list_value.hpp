#pragma once

#include <vector>

#include "../../Core/gm_common_header.h"
#include "../gm_value.hpp"
#include "../gm_types.h"

namespace GM
{
    class GM_Value;
    class GM_Object;
    class GM_Environment;

    class GM_ListValue : extends(GM_Value)
    {

    public:
        GM_ListValue (GM_Environment* env);
        virtual ~GM_ListValue ();

    public:
        GM_VALUE_DEBUG_STR_FUNC(GM_ListValue)
        GM_VALUE_STR_FUNC(list)

        std::string _str() const override;

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_LIST_VALUE;
        }

        GM_ListValue* add_item(GM_Value* value);
        GM_ListValue* remove_item(const size_t& index);
        GM_ListValue* set_item(const size_t& index, GM_Value* value);
        GM_Value* get_item(const size_t& index) const;

        size_t get_item_count() const;

        GM_Value* operator[] (const size_t& index) const;

    protected:
        void _init_functions() override;

    protected:
        std::vector<GM_Value*>* m_items;

    private:
        GM_STATIC_FUNCTION_D(__add);
        GM_STATIC_FUNCTION_D(__sub);
        GM_STATIC_FUNCTION_D(__set);
        GM_STATIC_FUNCTION_D(__get);
    };

}
