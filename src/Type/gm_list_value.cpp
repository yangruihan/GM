#include "gm_list_value.hpp"

namespace GM
{

    GM_ListValue::~GM_ListValue ()
    {
        if (m_items != nullptr)
            delete[] m_items;
    }

    void GM_ListValue::add_item(GM_Value* value)
    {
        if (value == nullptr)
        {
            PRINT_ERROR_F("Nullptr Error: list value add nullptr item");
            return;
        }

        m_items->push_back(value);
    }

    size_t GM_ListValue::get_item_count() const
    {
        return m_items->size();
    }

    GM_Value* GM_ListValue::operator[] (int index) const
    {
        if (index < 0 || index >= get_item_count())
        {
            PRINT_ERROR_F("IndexError: index(%d) out of range(%d)", index, get_item_count());
            return nullptr;
        }

        return m_items->at(index);
    }

}