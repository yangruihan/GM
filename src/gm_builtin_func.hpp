#pragma once

#include "gm_common_header.h"

#define BUILTIN_FUNC_PRINT  "print"
#define BUILTIN_FUNC_EXIT   "exit"

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
        static GM_Value* __print(const GM_Parameter* param);

        static GM_Value* __exit(const GM_Parameter* param);


    };

}
