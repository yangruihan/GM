#pragma once

#include <string>
#include <stack>

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
    class GM_Object;
    class GM_AST_TREE;
    class GM_Environment;

    class GM_Interpreter : extends(GM_Object)
    {

    private:
        class GM_InterpreterData
        {
        public:
            GM_Environment* m_environment;

            GM_AST_TREE* m_ast_root;

            size_t m_parse_cursor;

            std::stack<size_t>* m_token_index_stack;
            size_t m_current_token_index;

            size_t m_parse_mode;        // Parse Mode: (REPL | Source file)

            GM_InterpreterData()
            {
                m_ast_root = nullptr;
                m_parse_cursor = 0;
                m_token_index_stack = new std::stack<size_t>();
                m_current_token_index = 0;
            }

            ~GM_InterpreterData()
            {
                delete m_token_index_stack;
            }

            static bool create(GM_InterpreterData*& instance,
                               GM_Environment* env,
                               const size_t& parse_mode);

        };

    private:
        GM_Interpreter();
        ~GM_Interpreter() override;

    public:
        GM_Interpreter(GM_Interpreter& other) = delete;
        void operator=(const GM_Interpreter& other) = delete;

        static GM_Interpreter* instance();

        static void destory();

    private:
        static GM_Interpreter* s_ins;

    public:
        int repl();
        int parse_file(const std::string& file_path);

        int parse_and_eval(const std::string& command);

        int parse(const std::string& command);
        GM_Value* eval() const;

    public:
        bool init();

        std::string str() const override { return "interpreter"; }

        GM_AST_TREE* get_ast_root() const
        {
            return m_data_stack->top()->m_ast_root;
        }

        bool get_running_flag() const;

        GM_Value* get_var_from_loaded_env(const std::string& var_name);

        GM_Environment* get_global_env() const { return m_global_environment; }

    private:
        void set_parse_mode(const size_t& mode)
        {
            m_data_stack->top()->m_parse_mode = mode;
        }

        size_t get_parse_mode() const
        {
             return m_data_stack->top()->m_parse_mode;
        }

        GM_InterpreterData* get_current_data() const
        {
            return m_data_stack->top();
        }

    private:
        bool _create_data(const size_t& parse_mode);
        bool _clear_data() const;

        GM_AST_TREE* _parse(const std::string& command, GM_Environment* env);

        GM_AST_TREE* _get_ast_tree_from_token(const std::string& token) const;

        bool _take_token(const std::string& command, std::string& token);
    
    private:
        std::stack<GM_InterpreterData*>* m_data_stack;

        std::vector<GM_Environment*>* m_loaded_env;

        GM_Environment* m_global_environment;

#ifdef DEBUG
        void _print_ast(GM_AST_TREE* node, int indent) const;
#endif
    };

}
