#pragma once

#include <vector>

#include "../../gm_common_header.h"
#include "../gm_value.hpp"
#include "../gm_types.h"

namespace GM
{
    class GM_Value;
    class GM_Environment;

    class GM_PairValue : extends(GM_Value)
    {
    public:
        GM_PairValue (GM_Environment* env,
                      const std::string& key,
                      GM_Value* value);
        virtual ~GM_PairValue ();

    public:
        GM_VALUE_STR_FUNC(GM_PairValue)

        std::string _str() const override;

    public:
        VALUE_TYPE get_type() const override
        {
            return T_GM_PAIR_VALUE;
        }

        std::string get_key() const { return m_key; }
        GM_Value* get_value() const { return m_value; }
    
    protected:
        void _init_functions() override;

    protected:
        std::string m_key;
        GM_Value* m_value;

    };
    
}
