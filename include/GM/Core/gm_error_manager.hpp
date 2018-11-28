#pragma once

#include <string>

namespace GM
{

    void error(const size_t& line, const std::string& msg);

    void report(const size_t& line, const std::string& where, const std::string& msg);

}
