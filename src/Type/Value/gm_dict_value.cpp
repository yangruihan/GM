#include "gm_dict_value.hpp"
#include "../../GM.h"

#include <sstream>

namespace GM
{

    GM_DictValue::GM_DictValue(GM_Environment* env)
                                            : GM_Value(env)
    {
        m_items = new std::map<std::string, GM_PairValue*>();
    }
    
    GM_DictValue::~GM_DictValue()
    {
        delete m_items;
    }
    
    std::string GM_DictValue::str() const
    {
        std::ostringstream stream;
        stream << "{" << std::endl;
        for (auto it = m_items->begin(); it != m_items->end(); it++)
        {
            stream << "\t\"" << it->first << "\": " << it->second->str() << ",\n";
        }
        stream << "}" << std::endl;
        return stream.str();
    }
    
    void GM_DictValue::_init_functions()
    {}

    GM_DictValue* GM_DictValue::add_item(const std::string& key,
                                                     GM_PairValue *value)
    {
        (*m_items)[key] = value;
        return this;
    }

    GM_PairValue* GM_DictValue::operator[] (const std::string& key) const
    {
        auto it = m_items->find(key);
        if (it != m_items->end())
            return it->second;

        return nullptr;
    }

    size_t GM_DictValue::get_item_count() const
    {
        return m_items->size();
    }

}

