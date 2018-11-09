#include "gm_list_value.hpp"
#include <sstream>

#include "../../GM.h"

namespace GM
{
    GM_ListValue::GM_ListValue(GM_Environment* env): GM_Value(env)
    {
        m_items = new std::vector<GM_Value*>();

        _init_functions();
    }
    
    GM_ListValue::~GM_ListValue ()
    {
        delete m_items;
    }

    void GM_ListValue::_init_functions()
    {
        GM_VALUE_SET_SELF_FUNCTION(FUNC_ADD_OP_KEY, 2, GM_ListValue::__add);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_SUB_OP_KEY, 2, GM_ListValue::__sub);
    }

    std::string GM_ListValue::_str() const
    {
        if (m_items->size() == 0)
            return "[]";

        std::ostringstream stream;
        stream << "[";
        
        for (size_t i = 0; i < m_items->size() - 1; i++)
        {
            stream << m_items->at(i)->str() << ", ";
        }

        stream << m_items->at(m_items->size() - 1)->str() << "]";

        return stream.str();
    }

    GM_ListValue* GM_ListValue::add_item(GM_Value* value)
    {
        if (value == nullptr)
        {
            PRINT_ERROR_F("Nullptr Error: list value add nullptr item");
            return this;
        }

        m_items->push_back(value);

        return this;
    }

    GM_ListValue* GM_ListValue::remove_item(const size_t &index)
    {
        if (index >= m_items->size())
        {
            PRINT_ERROR_F("IndexError: index(%zu) is out of range(%zu)", index, m_items->size());
            return this;
        }

        m_items->erase(m_items->begin() + index);

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

    GM_FUNCTION_I(GM_ListValue, __add)
    {
        auto self = param->get_param<GM_ListValue>(0);
        auto value = param->get_param<GM_Value>(1);

        if (self != nullptr && value != nullptr)
        {
            self->add_item(value);
        }

        return self;
    }

    GM_FUNCTION_I(GM_ListValue, __sub)
    {
        auto self = param->get_param<GM_ListValue>(0);
        auto value = param->get_param<GM_IntValue>(1);

        if (self != nullptr && value != nullptr)
        {
            self->remove_item((size_t)value->get_value());
        }

        return self;
    }

}
