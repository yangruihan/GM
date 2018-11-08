#include "gm_list_value.hpp"
#include <sstream>

#include "../../GM.h"

namespace GM
{
    GM_ListValue::GM_ListValue(GM_Environment* env): GM_Value(env)
    {
        m_items = new std::vector<GM_Value*>();
    }
    
    GM_ListValue::~GM_ListValue ()
    {
        delete m_items;
    }

    void GM_ListValue::_init_functions()
    {
    }

    std::string GM_ListValue::_str() const
    {
        if (m_items->size() == 0)
            return "[]";

        std::ostringstream stream;
        stream << "[";
        
        for (size_t i = 0; i < m_items->size() - 1; i++)
        {
            stream << m_items->at(i)->_str() << ", ";
        }

        stream << m_items->at(m_items->size() - 1)->_str() << "]";

        return stream.str();
    }

    GM_ListValue* GM_ListValue::add_item(GM_Value* value)
    {
        if (value == nullptr)
        {
            PRINT_ERROR_F("Nullptr Error: list value add nullptr item");
            return nullptr;
        }

        m_items->push_back(value);

        return this;
    }

    size_t GM_ListValue::get_item_count() const
    {
        return m_items->size();
    }

    GM_Value* GM_ListValue::operator[] (int index) const
    {
        if (index < 0 || index >= get_item_count())
        {
            PRINT_ERROR_F("IndexError: index(%d) out of range(%ld)", index, get_item_count());
            return nullptr;
        }

        return m_items->at(index);
    }

}
