#include "gm_interpreter.hpp"
#include "GM.h"

#define CHECK_TOKEN(func) \
do { \
ret = GM_InterpreterUtils::func(token); \
if (ret != nullptr) \
    return ret;     \
} while(0)

namespace GM
{

    GM_Interpreter::GM_Interpreter()
    {
        m_environment = new GM_Environment();
        init();
    }
    
    GM_Interpreter::~GM_Interpreter() 
    {
        delete m_token_index_stack;
        delete m_environment;
        delete m_ast_root;
    }

    GM_Interpreter* GM_Interpreter::s_ins = new GM_Interpreter();

    GM_Interpreter* GM_Interpreter::instance()
    {
        return s_ins;
    }

    void GM_Interpreter::destory()
    {
        delete s_ins;
    }

    bool GM_Interpreter::init()
    {
        m_token_index_stack = new std::stack<size_t>();

        m_environment->set_var(GM_INTERPRETER_RUN_FLAG,
                               GM_Value::bool_value(m_environment, true));

        auto ret = GM_BuiltinFunc::init(m_environment);
        return ret;
    }

    bool GM_Interpreter::get_running_flag() const
    {
        auto flag = m_environment->get_var(GM_INTERPRETER_RUN_FLAG);
        return dynamic_cast<GM_BoolValue*>(flag)->get_value();
    }

    int GM_Interpreter::repl()
    {
        set_parse_mode(GM_INTERPRETER_REPL_MODE);

        std::string command;
        int ret = 0;
        bool running_flag = true;
        while (ret == 0 && running_flag)
        {
            std::cout << "> ";
            std::getline(std::cin, command);

            DEBUG_LOG_F("-- Input: %s", command.c_str());

            ret = parse_and_eval(command);

            running_flag = get_running_flag();
        }

        return ret;
    }

    int GM_Interpreter::parse_file(const std::string &file_path)
    {
        set_parse_mode(GM_INTERPRETER_FILE_MODE);

        int ret = 0;
        if (GM_Utils::str_ends_with(file_path, GM_SOURCE_FILE_SUFFIX))
        {
            std::string file_content;
            if (GM_Utils::read_file(file_path.c_str(), file_content))
            {
                DEBUG_LOG_F("File content: %s", file_content.c_str());

                ret = parse_and_eval(file_content);
            }
            else
            {
                ret = -1;
                PRINT_ERROR_F("IOError: file(%s) read failed", file_path.c_str());
            }
        }

        return ret;
    }

    int GM_Interpreter::parse_and_eval(const std::string& command)
    {
        m_start_pos = 0;

        auto command_len = command.size();
        auto ret = 0;

        while (m_start_pos < command_len - 1)
        {
            ret = this->parse(command);

            if (ret == 0)
            {
#ifdef DEBUG
                DEBUG_LOG_F("Create AST success");
                DEBUG_LOG_F("--- Show AST structure ---");
                auto root = this->get_ast_root();
                this->_print_ast(root, 0);
                std::cout << std::endl;
#endif

                auto result = this->eval();
                if (result != nullptr)
                {
                    ret = 0;

#ifdef DEBUG
                    DEBUG_LOG_F("--------------------");
                    DEBUG_LOG_F("- Expr: %s", command.c_str());
                    DEBUG_LOG_F("- Result: %s", result->str().c_str());
                    DEBUG_LOG_F("--------------------");
#else
                    if (m_parse_mode == GM_INTERPRETER_REPL_MODE)
                        std::cout << result->str().c_str() << std::endl;
#endif
                }
                else
                {
                    ret = -1;
                }
            }
            else
            {
                std::cout << "Error Code: " << ret << std::endl;
                break;
            }
        }

        return ret;
    }

    GM_Value* GM_Interpreter::eval() const
    {
        auto root = get_ast_root();
        
        if (root != nullptr)
        {
            return root->eval();
        }

        PRINT_ERROR("NullptrError: ast root is nullptr");
        return nullptr;
    }

    int GM_Interpreter::parse(const std::string& command)
    {
        m_current_token_index = 0;

        m_ast_root = _parse(command, m_environment);

        if (m_ast_root == nullptr)
            return -1;

        return 0;
    }

    GM_AST_TREE* GM_Interpreter::_parse(const std::string& command,
                                        GM_Environment* env)
    {
        if (m_start_pos >= command.size())
            return nullptr;

        GM_AST_TREE* ret = nullptr;
        std::string token;
        bool is_func;
        if (_take_token(command, token, is_func))
        {
            DEBUG_LOG_F("Get Token %s (%zu, %zu)",
                        token.c_str(),
                        m_token_index_stack->size(),
                        m_current_token_index);

            ret = _get_ast_tree_from_token(token);

            if (ret == nullptr)
            {
                // TODO invalid
            }
            else
            {
                // set token index for AST Node
                ret->set_token_index(m_current_token_index);

                if (command[m_start_pos - 1] == ')')
                {
                    m_current_token_index = m_token_index_stack->top();
                    m_token_index_stack->pop();
                }
                else
                {
                    m_current_token_index ++;
                }

                auto new_env = ret->set_environment(env);

                DEBUG_LOG_F("Create AST Node %s, child count %zu",
                            ret->get_token().c_str(),
                            ret->get_need_child_count());

                auto child_count = ret->get_need_child_count();

                // variadic parameter
                if (child_count == GM_AST_VARIADIC_PARAMS_FLAG)
                {
                    if (is_func)
                    {
                        auto parentheses_count = m_token_index_stack->size();
                        auto command_len = command.size();
                        while (m_start_pos < command_len
                               && m_token_index_stack->size() >= parentheses_count)
                        {
                            ret->add_child(_parse(command, new_env));

                            while (command[m_start_pos] == ')'
                                   || GM_Utils::is_space(command[m_start_pos]))
                            {
                                if (command[m_start_pos] == ')')
                                {
                                    m_current_token_index = m_token_index_stack->top();
                                    m_token_index_stack->pop();
                                }

                                m_start_pos++;
                            }
                        }
                    }
                }
                // fixed parameter
                else
                {
                    for (size_t i = 0; i < child_count; i++)
                    {
                        ret->add_child(_parse(command, new_env));
                    }

                    while (command[m_start_pos] == ')'
                           || GM_Utils::is_space(command[m_start_pos]))
                    {
                        if (command[m_start_pos] == ')')
                        {
                            m_current_token_index = m_token_index_stack->top();
                            m_token_index_stack->pop();
                        }

                        m_start_pos++;
                    }
                }
            }
        }

        return ret;
    }

    GM_AST_TREE* GM_Interpreter::_get_ast_tree_from_token(const std::string& token) const
    {
        auto token_size = token.size();
        if (token_size == 0 || token[0] == ' ')
            return new GM_AST_NULL_EXPR("");

        GM_AST_TREE* ret;
        
        if (token_size == 1)
        {
            CHECK_TOKEN(check_token_is_operator);
        }

        // digit
        CHECK_TOKEN(check_token_is_number_literal);
        
        // str
        CHECK_TOKEN(check_token_is_str_literal);

        // list
        CHECK_TOKEN(check_token_is_list);

        // dict
        CHECK_TOKEN(check_token_is_dict);

        // variable
        CHECK_TOKEN(check_token_is_variable);

        PRINT_ERROR_F("SyntaxError: token(%s) is error", token.c_str());
        return nullptr;
    }

    bool GM_Interpreter::_take_token(const std::string& command, std::string& token, bool& is_func)
    {
        auto command_len = command.size();
        if (command_len == 0)
        {
            DEBUG_ERROR("Command is empty");
            return false;
        }

        auto start_pos = m_start_pos;
        auto end_pos = m_start_pos;
        
        auto left_parentheses = false;
        auto quotation_mark = false;
        
        char c;
        while (end_pos < command_len)
        {
            c = command[end_pos];
            if (c == '\0')
            {
                if (left_parentheses)
                {
                    PRINT_ERROR("Syntax Error: no matching right parenthesis");
                    m_start_pos = command_len;
                    return false;
                }
                else
                {
                    token = command.substr(start_pos, end_pos - start_pos);
                    DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, end_pos);
                    m_start_pos = end_pos + 1;
                    return true;
                }
            }
            else if (c == '(')
            {
                if (left_parentheses)
                {
                    PRINT_ERROR("Syntax Error: double left parenthesis");
                    m_start_pos = command_len;
                    return false;
                }
                else
                {
                    m_token_index_stack->push(m_current_token_index);
                    m_current_token_index = 0;

                    left_parentheses = true;
                    is_func = true;
                    start_pos++;
                    end_pos++;
                    continue;
                }
            }
            else if (c == ')')
            {
                if (m_token_index_stack->size() == 0)
                {
                    PRINT_ERROR("Syntax Error: no matching left parenthesis");
                    m_start_pos = command_len;
                    return false;
                }

                if (command[end_pos - 1] == '(')
                {
                    m_start_pos = end_pos + 1;
                    token = "";
                    return true;
                }
                else if (end_pos == start_pos)
                {
                    start_pos++;
                    end_pos++;
                    continue;
                }

                token = command.substr(start_pos, end_pos - start_pos);
                DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, end_pos);
                m_start_pos = end_pos + 1;
                return true;
            }
            else if (GM_Utils::is_space(c))
            {
                if (end_pos == start_pos)
                {
                    start_pos++;
                    end_pos++;
                    continue;
                }

                if (!quotation_mark)
                {
                    token = command.substr(start_pos, end_pos - start_pos);
                    DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, end_pos);
                    m_start_pos = end_pos + 1;
                    return true;
                }
            }
            else if (c == '"')
            {
                quotation_mark = !quotation_mark;
            }

            end_pos++;
        }

        return false;
    }

#ifdef DEBUG

    void GM_Interpreter::_print_ast(GM_AST_TREE* node, int indent) const
    {
        if (node == nullptr)
        {
            DEBUG_ERROR("node is nullptr");
            return;
        }

        std::cout << std::endl;

        for (size_t i = 0; i < indent; i++)
        {
            std::cout << "\t";
        }

        std::cout << node->str();

        for (size_t i = 0; i < node->get_child_count(); i++)
        {
            _print_ast(node->get_child(i), indent + 1);
        }
    }

#endif

}
