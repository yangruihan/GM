#include "gm_builtin_func.hpp"
#include "GM.h"

#include <iostream>

namespace GM
{

    bool GM_BuiltinFunc::init(GM_Environment* env)
    {
        env->set_var(BUILTIN_FUNC_PRINT, GM_Function::create_func(BUILTIN_FUNC_PRINT,
                                                                  1,
                                                                  GM_BuiltinFunc::__print));

        return true;
    }

    GM_Value* GM_BuiltinFunc::__print(const GM_Parameter* param)
    {
        auto value = param->get_param<GM_Value>(0);
        if (value == nullptr)
        {
            std::cout << "nullptr" << std::endl;
            return new GM_StrValue("nullptr");
        }
        else
        {
            auto str = value->str();
            std::cout << str << std::endl;
            return new GM_StrValue(str);
        }
    }

}
