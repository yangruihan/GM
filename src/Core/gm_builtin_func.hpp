#pragma once

#include "gm_common_header.h"

namespace GM
{
    class GM_Value;
    class GM_Parameter;
    class GM_Environment;

    class GM_BuiltinFunc : extends(GM_Object)
    {

    public:
        static bool init(GM_Environment* env);

    private:
        GM_STATIC_FUNCTION_D(__print);
        GM_STATIC_FUNCTION_D(__exit);
        GM_STATIC_FUNCTION_D(__let);
        GM_STATIC_FUNCTION_D(__for);

        GM_STATIC_FUNCTION_D(__ls);     // <
        GM_STATIC_FUNCTION_D(__eq);     // =
        GM_STATIC_FUNCTION_D(__gt);     // >
        GM_STATIC_FUNCTION_D(__le);     // <=
        GM_STATIC_FUNCTION_D(__ge);     // >=
        GM_STATIC_FUNCTION_D(__ne);     // !=

        GM_STATIC_FUNCTION_D(__def);
        GM_STATIC_FUNCTION_D(__if);
        GM_STATIC_FUNCTION_D(__pair);
        GM_STATIC_FUNCTION_D(__import);

        GM_STATIC_FUNCTION_D(__get);
        GM_STATIC_FUNCTION_D(__set);
        
    };

}
