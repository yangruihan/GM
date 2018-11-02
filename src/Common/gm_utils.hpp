#pragma once

#include <stdio.h>
#include <iostream>
#include <ctype.h>

#define _PRINT(content) std::cout << (content)
#define _PRINT_F(format, ...) printf((format), ##__VA_ARGS__)

#define PRINT(level, content) _PRINT(level); _PRINT(" "); _PRINT(content); _PRINT("\n")
#define PRINT_F(level, format, ...) _PRINT(level); _PRINT(" "); _PRINT_F(format, ##__VA_ARGS__); _PRINT("\n")

#define DEBUG_LOG(content) PRINT("[LOG]", content)
#define DEBUG_LOG_F(format, ...) PRINT_F("[LOG]", format, ##__VA_ARGS__)

#define DEBUG_WARNING(content) PRINT("[WARNING]", content)
#define DEBUG_WARNING_F(format, ...) PRINT_F("[WARNING]", format, ##__VA_ARGS__)

#define DEBUG_ERROR(content) PRINT("[ERROR]", content)
#define DEBUG_ERROR_F(format, ...) PRINT_F("[ERROR]", format, ##__VA_ARGS__)

namespace GM
{
    class GM_Utils
    {

    public:
        static bool is_digit(char c)
        {
            return isdigit(c);
        }

    };
}
