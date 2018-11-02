#pragma once

#include <string>

#include "GM.h"
#include "gm_environment.hpp"

namespace GM
{

    class GM_Interpreter : extends(GM_Object)
    {
    public:
        GM_Interpreter();
        ~GM_Interpreter() override;

        int parse(std::string* command) const;
    
    private:
        GM_Environment* m_environment;
    };

}