#pragma once

#include <string>

#include "gm_common_header.h"
#include "gm_environment.hpp"
#include "AST/gm_ast_header.h"
#include "Type/gm_types_header.h"

//#define GM_TOKEN_C_ENDLINE  100     // \0
//#define GM_TOKEN_C_LEFT_P   101     // (
//#define GM_TOKEN_C_RIGHT_P  102     // )
//#define GM_TOKEN_C_SPACE    103     // \t \n
//#define GM_TOKEN_C_QUOT     104     // "

namespace GM
{

    class GM_Interpreter : extends(GM_Object)
    {
    public:
        GM_Interpreter();
        ~GM_Interpreter() override;

        bool init();

        int parse(const std::string& command);
        GM_Value* eval() const;
        int parse_and_eval(const std::string& command);

    public:
        std::string str() const override { return "interpreter"; }

        GM_AST_TREE* get_ast_root() const { return m_ast_root; }

        bool get_running_flag() const;

        void set_parse_mode(const size_t& mode) { m_parse_mode = mode; }
        size_t get_parse_mode() const { return m_parse_mode; }

    private:
        GM_AST_TREE* _parse(const std::string& command, GM_Environment* env);

        GM_AST_TREE* _get_ast_tree_from_token(const std::string& token) const;

        bool _take_token(const std::string& command, std::string& token, bool& is_func);
    
    private:
        GM_Environment* m_environment;
        GM_AST_TREE* m_ast_root;
        
        size_t m_start_pos;
        size_t m_left_parentheses_count;

        size_t m_parse_mode;

#ifdef DEBUG
        void _print_ast(GM_AST_TREE* node, int indent) const;
#endif
    };

}
