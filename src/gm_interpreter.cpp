#include "gm_interpreter.hpp"
#include "GM.h"

namespace GM
{

    GM_Interpreter::GM_Interpreter()
    {
        m_environment = new GM_Environment();
    }
    
    GM_Interpreter::~GM_Interpreter() 
    {
        delete m_environment;
    }

    bool GM_Interpreter::init()
    {
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

    int GM_Interpreter::parse(std::string command)
    {
        m_start_pos = 0;
        m_left_parentheses_count = 0;

        m_ast_root = _parse(command, m_environment);

        if (m_ast_root == nullptr)
            return -1;

        return 0;
    }

    GM_AST_TREE* GM_Interpreter::_parse(std::string& command,
                                        GM_Environment* env)
    {
        if (m_start_pos >= command.size())
            return nullptr;

        GM_AST_TREE* ret = nullptr;
        std::string token;
        if (_take_token(command, token))
        {
            DEBUG_LOG_F("Get Token %s", token.c_str());
            
            if (token != "")
            {
                ret = _get_ast_tree_from_token(token);

                if (ret != nullptr)
                {
                    auto new_env = ret->set_environment(env);
                    
                    DEBUG_LOG_F("Create AST Node %s, child count %zu",
                                ret->get_token().c_str(),
                                ret->get_need_child_count());

                    auto child_count = ret->get_need_child_count();

                    // variadic parameter
                    if (child_count == GM_AST_VARIADIC_PARAMS_FLAG)
                    {
                        auto parentheses_count = m_left_parentheses_count;
                        while (m_left_parentheses_count >= parentheses_count)
                        {
                            ret->add_child(_parse(command, new_env));

                            if (m_left_parentheses_count == 1 && command[m_start_pos] == ')')
                                break;
                        }
                    }
                    // fixed parameter
                    else
                    {
                        for (size_t i = 0; i < child_count; i++)
                        {
                            ret->add_child(_parse(command, new_env));
                        }
                    }
                }
            }
        }

        return ret;
    }

    GM_AST_TREE* GM_Interpreter::_get_ast_tree_from_token(std::string& token) const
    {
        auto token_size = token.size();
        if (token_size == 0)
        {
            PRINT_ERROR("Token Error: token is empty");
            return nullptr;
        }
        
        GM_AST_TREE* ret;
        
        if (token_size == 1)
        {
            ret = GM_InterpreterUtils::check_token_is_operator(token);
            if (ret != nullptr)
                return ret;
        }

        // digit
        ret = GM_InterpreterUtils::check_token_is_number_literal(token);
        if (ret != nullptr)
            return ret;
        
        // str
        ret = GM_InterpreterUtils::check_token_is_str_literal(token);
        if (ret != nullptr)
            return ret;

        // list
        ret = GM_InterpreterUtils::check_token_is_list(token);
        if (ret != nullptr)
            return ret;

        // variable
        ret = GM_InterpreterUtils::check_token_is_variable(token);
        if (ret != nullptr)
            return ret;

        PRINT_ERROR_F("SyntaxError: token(%s) is error", token.c_str());
        return nullptr;
    }

    bool GM_Interpreter::_take_token(std::string command, std::string& token)
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
                    m_left_parentheses_count++;
                    left_parentheses = true;
                    start_pos++;
                    end_pos++;
                    continue;
                }
            }
            else if (c == ')')
            {
                if (m_left_parentheses_count == 0)
                {
                    PRINT_ERROR("Syntax Error: no matching left parenthesis");
                    m_start_pos = command_len;
                    return false;
                }

                m_left_parentheses_count--;
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

}
