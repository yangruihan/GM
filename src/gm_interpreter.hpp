#pragma once

#include <string>

#include "GM.h"
#include "gm_environment.hpp"
#include "AST/gm_ast.h"

namespace GM
{

    class GM_Interpreter : extends(GM_Object)
    {
    public:
        GM_Interpreter();
        ~GM_Interpreter() override;

        int parse(std::string command);

    private:
        GM_AST_TREE* _parse(std::string& command);

        GM_AST_TREE* _get_ast_tree_from_token(std::string& token) const;

        bool _take_token(std::string command, std::string& token);
    
    private:
        GM_Environment* m_environment;
        GM_AST_TREE* m_ast_root;
        size_t m_start_pos;
        size_t m_left_parentheses_count;
    };

}