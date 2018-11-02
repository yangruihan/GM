#include "gm_interpreter.hpp"
#include "Common/gm_utils.hpp"

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

    int GM_Interpreter::parse(std::string command)
    {
        m_start_pos = 0;
        m_left_parentheses_count = 0;

        m_ast_root = _parse(command);

        if (m_ast_root == nullptr)
            return -1;

        return 0;
    }

    GM_AST_TREE* GM_Interpreter::_parse(std::string& command)
    {
        if (m_start_pos >= command.size())
            return nullptr;

        GM_AST_TREE* ret = nullptr;
        std::string token;
        if (_take_token(command, token))
        {
            if (token != "")
            {
                ret = _get_ast_tree_from_token(token);

                if (ret != nullptr)
                {
                    auto child_count = ret->get_need_child_count();
                    for (size_t i = 0; i < child_count; i++)
                    {
                        ret->add_child(_parse(command));
                    }
                }
            }
        }

        return ret;
    }

    GM_AST_TREE* GM_Interpreter::_get_ast_tree_from_token(std::string& token) const
    {
        auto token_size = token.size();

        if (token_size == 1)
        {
            if (token[0] == '+')
            {
                return new GM_AST_PLUS_OPERATOR_EXPR();
            }
        }

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
        char c;
        auto left_parentheses = false;
        
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
                    DEBUG_LOG_F("%s sub (%d, %d)", command.c_str(), start_pos, end_pos);
                    m_start_pos = end_pos + 1;
                    return true;
                }
            }
            if (c == '(')
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
            else if (c == ')' || GM_Utils::is_space(c))
            {
                if (c == ')' && m_left_parentheses_count == 0)
                {
                    PRINT_ERROR("Syntax Error: no matching left parenthesis");
                    m_start_pos = command_len;
                    return false;
                }

                m_left_parentheses_count--;
                token = command.substr(start_pos, end_pos - start_pos);
                DEBUG_LOG_F("%s sub (%d, %d)", command.c_str(), start_pos, start_pos);
                m_start_pos = end_pos + 1;
                return true;
            }

            end_pos++;
        }

        return false;
    }

}