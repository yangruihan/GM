#pragma once

#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>
#include <stdarg.h>
#include <cstring>

#define _PRINT(content) std::cout << (content)
#define _PRINT_F(format, ...) printf((format), ##__VA_ARGS__)

#define PRINT(level, content) do { _PRINT(level); _PRINT(" "); _PRINT(content); _PRINT("\n"); } while (0)
#define PRINT_F(level, format, ...) do { _PRINT(level); _PRINT(" "); _PRINT_F(format, ##__VA_ARGS__); _PRINT("\n"); } while (0)

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
    class GM_AST_TREE;
    class GM_Environment;

    class GM_Utils
    {
    private:
        static inline char m_str_buffer[256];

    public:
        /**
         * This function checks whether the passed
         * character is alphabetic.
         */
        static bool is_digit(const char& c)
        {
            return isdigit(c);
        }
        
        /**
         * This function checks whether the passed
         * character is white-space.
         */
        static bool is_space(const char& c)
        {
            return isspace(c);
        }
        
        /**
         * This function checks whether the passed
         * character is alphabetic.
         */
        static bool is_alpha(const char& c)
        {
            return isalpha(c);
        }

        /**
         * This function checks whether the passed
         * character is alphanumeric.
         */
        static bool is_alpha_or_num(const char& c)
        {
            return isalnum(c);
        }

        static void get_int_from_str(const std::string& str, int& value)
        {
            value = std::stoi(str);
        }

        static void get_float_from_str(const std::string& str, double& value)
        {
            value = std::stod(str);
        }

        static std::string format_str(const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            std::vsnprintf(m_str_buffer, 256, format, args);
            va_end(args);
            return std::string(m_str_buffer);
        }
        
        template<typename InstanceType, typename CheckType>
        static CheckType* is_instance_of(InstanceType* instance)
        {
            if (instance == nullptr)
                return nullptr;
            
            return dynamic_cast<CheckType*>(instance);
        }
        
        template<typename InstanceType, typename CheckType>
        static CheckType* is_instance_of(InstanceType& instance)
        {
            return dynamic_cast<CheckType*>(&instance);
        }

        static GM_Environment* set_env_for_childs(GM_AST_TREE* tree, GM_Environment* new_env);

    };

}
