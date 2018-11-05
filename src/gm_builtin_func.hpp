#pragma once

#include "gm_common_header.h"

#define BUILTIN_FUNC_PRINT  "print"
#define BUILTIN_FUNC_EXIT   "exit"
#define BUILTIN_FUNC_LET    "let"
#define BUILTIN_FUNC_FOR    "for"
#define BUILTIN_FUNC_DEF    "def"
#define BUILTIN_FUNC_LS     "<"
#define BUILTIN_FUNC_EQ     "="
#define BUILTIN_FUNC_GT     ">"
#define BUILTIN_FUNC_LE     "<="
#define BUILTIN_FUNC_GE     ">="
#define BUILTIN_FUNC_NE     "!="

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

    };

}
