#pragma once

#include "GM.h"
#include "gm_environment.hpp"

namespace GM
{

    class GM_Interpreter : extends(GM_Object)
    {
    public:
        GM_Interpreter();
        ~GM_Interpreter() override;

        int parse(char* command);
    
    private:
        GM_Environment* m_environment;
    };

}