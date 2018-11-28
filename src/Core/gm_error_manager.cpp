#include "gm_error_manager.hpp"

#include "GM.h"

namespace GM
{
    void error(const size_t& line, const std::string& msg)
    {
        report(line, "", msg);
    }

    void report(const size_t& line, const std::string& where, const std::string& msg)
    {
        PRINT_ERROR_F("(Line: %zu) %s: %s", line, where.c_str(), msg.c_str());
    }

}
