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
                    ret->set_environment(m_environment);
                    
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
        
        GM_AST_TREE* ret;
        
        if (token_size == 1)
        {
            ret = GM_InterpreterUtils::check_token_is_operator(token);
            if (ret != nullptr)
                return ret;
            
            // TODO check is variable
        }

        // digit
        ret = GM_InterpreterUtils::check_token_is_number_literal(token);
        if (ret != nullptr)
            return ret;
        
        // str
        ret = GM_InterpreterUtils::check_token_is_str_literal(token);
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
                DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, start_pos);
                m_start_pos = end_pos + 1;
                return true;
            }
            else if (GM_Utils::is_space(c))
            {
                if (!quotation_mark)
                {
                    token = command.substr(start_pos, end_pos - start_pos);
                    DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, start_pos);
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
