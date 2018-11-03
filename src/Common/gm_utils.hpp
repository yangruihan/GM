#pragma once

#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>

#define _PRINT(content) std::cout << (content)
#define _PRINT_F(format, ...) printf((format), ##__VA_ARGS__)

#define PRINT(level, content) _PRINT(level); _PRINT(" "); _PRINT(content); _PRINT("\n")
#define PRINT_F(level, format, ...) _PRINT(level); _PRINT(" "); _PRINT_F(format, ##__VA_ARGS__); _PRINT("\n")

#ifdef DEBUG
    #define DEBUG_LOG(content) PRINT("[DEBUG LOG]", content)
#else
    #define DEBUG_LOG(content)
#endif

#ifdef DEBUG
    #define DEBUG_LOG_F(format, ...) PRINT_F("[DEBUG LOG]", format, ##__VA_ARGS__)
#else
    #define DEBUG_LOG_F(format, ...)
#endif

#ifdef DEBUG
    #define DEBUG_WARNING(content) PRINT("[DEBUG WARNING]", content)
#else
    #define DEBUG_WARNING(content)
#endif

#ifdef DEBUG
    #define DEBUG_WARNING_F(format, ...) PRINT_F("[DEBUG WARNING]", format, ##__VA_ARGS__)
#else
    #define DEBUG_WARNING_F(format, ...)
#endif

#ifdef DEBUG
    #define DEBUG_ERROR(content) PRINT("[DEBUG ERROR]", content)
#else
    #define DEBUG_ERROR(content)
#endif

#ifdef DEBUG
    #define DEBUG_ERROR_F(format, ...) PRINT_F("[DEBUG ERROR]", format, ##__VA_ARGS__)
#else
    #define DEBUG_ERROR_F(format, ...)
#endif

#define PRINT_LOG(content) PRINT("[LOG]", content)
#define PRINT_LOG_F(format, ...) PRINT_F("[LOG]", format, ##__VA_ARGS__)

#define PRINT_WARNING(content) PRINT("[WARNING]", content)
#define PRINT_WARNING_F(format, ...) PRINT_F("[WARNING]", format, ##__VA_ARGS__)

#define PRINT_ERROR(content) PRINT("[ERROR]", content)
#define PRINT_ERROR_F(format, ...) PRINT_F("[ERROR]", format, ##__VA_ARGS__)

namespace GM
{
    class GM_Utils
    {

    public:
        static bool is_digit(char c)
        {
            return isdigit(c);
        }

        static bool is_space(char c)
        {
            return isspace(c);
        }

        static void get_int_from_str(std::string& str, int& value)
        {
            value = std::stoi(str);
        }

        static void get_float_from_str(std::string& str, double& value)
        {
            value = std::stod(str);
        }
    };
}
