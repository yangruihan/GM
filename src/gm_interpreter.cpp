#include "gm_interpreter.hpp"

#include <iostream>

namespace GM
{

    GM_Interpreter::GM_Interpreter()
    {
        m_environment = new GM_Environment();
    }
    
    GM_Interpreter::~GM_Interpreter() 
    {
        delete m_environment;
    }

    int GM_Interpreter::parse(std::string* command) const
    {
        std::cout << *command << std::endl;
        return 0;
    }

}