#pragma once

#define VALUE_TYPE size_t

#define T_GM_VALUE              100
#define T_GM_NUMBER_VALUE       101
#define T_GM_INT_VALUE          102
#define T_GM_FLOAT_VALUE        103
#define T_GM_STR_VALUE          104
#define T_GM_LIST_VALUE         105
#define T_GM_DICTIONARY_VALUE   106
#define T_GM_BOOL_VALUE         107
#define T_GM_NULL_VALUE         108

namespace GM
{

    class GM_TypeUtils
    {

    public:

        static bool is_number_type(VALUE_TYPE& t)
        {
            if (t == T_GM_FLOAT_VALUE || t == T_GM_INT_VALUE)
            {
                return true;
            }

            return false;
        }

    };

}
