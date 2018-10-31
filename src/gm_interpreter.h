#pragma once

#include "GM.h"
#include "gm_environment.h"

namespace GM
{

    class GM_Interpreter : GM_Object
    {
    public:
        GM_Interpreter();
        virtual ~GM_Interpreter();

        int parse(char* command);
    
    private:
        GM_Environment* m_environment;
    };

}