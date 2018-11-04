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
        delete[] m_environment;
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
            DEBUG_LOG_F("Get Token %s", token.c_str());
            
            if (token != "")
            {
                ret = _get_ast_tree_from_token(token);

                if (ret != nullptr)
                {
                    DEBUG_LOG_F("Create AST Node %s, child count %ld",
                                ret->get_token().c_str(),
                                ret->get_need_child_count());

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
        if (token_size == 0)
        {
            PRINT_ERROR("Token Error: token is empty");
            return nullptr;
        }
        
        if (token_size == 1)
        {
            if (GM_AST_ADD_OPERATOR_EXPR::check_token_valid(token))
            {
                return new GM_AST_ADD_OPERATOR_EXPR(token);
            }
            else if (GM_AST_SUB_OPERATOR_EXPR::check_token_valid(token))
            {
                return new GM_AST_SUB_OPERATOR_EXPR(token);
            }
            else if (GM_AST_MUL_OPERATOR_EXPR::check_token_valid(token))
            {
                return new GM_AST_MUL_OPERATOR_EXPR(token);
            }
            else if (GM_AST_DIV_OPERATOR_EXPR::check_token_valid(token))
            {
                return new GM_AST_DIV_OPERATOR_EXPR(token);
            }
        }

        // digit
        if (GM_Utils::is_digit(token[0])
            || (token_size > 1 && (token[0] == '+' || token[0] == '-')))
        {
            bool is_float;
            if (GM_AST_NUMBER_LITERAL_EXPR::check_token_valid(token, is_float))
            {
                return new GM_AST_NUMBER_LITERAL_EXPR(token, is_float);
            }
        }

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
                    DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, end_pos);
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
                DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, start_pos);
                m_start_pos = end_pos + 1;
                return true;
            }

            end_pos++;
        }

        return false;
    }

}
