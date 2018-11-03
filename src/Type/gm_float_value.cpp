#include "gm_float_value.hpp"
#include "../Common/gm_utils.hpp"

namespace GM
{

    GM_FloatValue::GM_FloatValue(std::string& token)
    {
        GM_Utils::get_float_from_str(token, m_value);

        _init_functions();
    }

    GM_FloatValue::GM_FloatValue(int value): m_value(value)
    {
        _init_functions();
    }

    GM_FloatValue::GM_FloatValue(double value): m_value(value)
    {
        _init_functions();
    }

    void GM_FloatValue::_init_functions()
    {
    }

    std::string GM_FloatValue::str()
    {
        return GM_Utils::format_str("%lf", m_value);
    }

}