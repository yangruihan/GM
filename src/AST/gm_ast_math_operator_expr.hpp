#pragma once

#include "../GM.h"
#include "gm_ast_binary_expr.hpp"

namespace GM
{

    class GM_AST_PLUS_OPERATOR_EXPR : extends(GM_AST_BINARY_EXPR)
    {

    public:
        GM_AST_PLUS_OPERATOR_EXPR (std::string& token): GM_AST_BINARY_EXPR(token) {}
        ~GM_AST_PLUS_OPERATOR_EXPR () override {}

    public:
        size_t get_need_child_count() const override { return 2; };

        static bool check_token_valid(std::string& token)
        {
            return token.size() == 1 && token[0] == '+';
        }

    };

    class GM_AST_SUB_OPERATOR_EXPR : extends(GM_AST_BINARY_EXPR)
    {

    public:
        GM_AST_SUB_OPERATOR_EXPR (std::string& token): GM_AST_BINARY_EXPR(token) {}
        ~GM_AST_SUB_OPERATOR_EXPR () override {}

    public:
        size_t get_need_child_count() const override { return 2; };

        static bool check_token_valid(std::string& token)
        {
            return token.size() == 1 && token[0] == '-';
        }

    };

    class GM_AST_MUL_OPERATOR_EXPR : extends(GM_AST_BINARY_EXPR)
    {

    public:
        GM_AST_MUL_OPERATOR_EXPR (std::string& token): GM_AST_BINARY_EXPR(token) {}
        ~GM_AST_MUL_OPERATOR_EXPR () override {}

    public:
        size_t get_need_child_count() const override { return 2; };

        static bool check_token_valid(std::string& token)
        {
            return token.size() == 1 && token[0] == '*';
        }

    };

    class GM_AST_DIV_OPERATOR_EXPR : extends(GM_AST_BINARY_EXPR)
    {

    public:
        GM_AST_DIV_OPERATOR_EXPR (std::string& token): GM_AST_BINARY_EXPR(token) {}
        ~GM_AST_DIV_OPERATOR_EXPR () override {}

    public:
        size_t get_need_child_count() const override { return 2; };

        static bool check_token_valid(std::string& token)
        {
            return token.size() == 1 && token[0] == '/';
        }

    };
}
