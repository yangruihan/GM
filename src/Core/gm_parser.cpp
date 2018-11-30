#include "gm_parser.hpp"
#include "GM.h"

namespace GM
{

    GM_Parser::GM_Parser()
        : m_tokens(nullptr),
          m_curt_idx(0)
    {
    }

    GM_AST_TREE* GM_Parser::parse(const std::vector<GM_Token*>* tokens)
    {
        if (tokens == nullptr)
        {
            PRINT_ERROR_F("ParserError: tokens is null");
            return nullptr;
        }

        m_tokens = const_cast<std::vector<GM_Token*>*>(tokens);
        return _expr();
    }

    GM_AST_TREE* GM_Parser::_expr()
    {
        if (_check(GM_VAR))
            return _assignment_expr();

        return _arithmetic_expr();
    }

    GM_AST_TREE* GM_Parser::_arithmetic_expr()
    {
        return _equality();
    }

    GM_AST_TREE* GM_Parser::_equality()
    {
        auto comp = _comparison();

        while (_match(GM_BANG_EQ) || _match(GM_EQ))
        {
            auto token = _peek(-1);
            auto right = _comparison();
            auto node = GM_GC::alloc_args<GM_AST_VAR_EXPR>(token->m_word);
            node->add_childs(2, comp, right);
            comp = node;
        }

        return comp;
    }

    GM_AST_TREE* GM_Parser::_comparison()
    {
        auto add = _addition();

        while (_match(GM_GREATER) || _match(GM_GREATER_EQ)
               || _match(GM_LESS) || _match(GM_LESS_EQ))
        {
            auto token = _peek(-1);
            auto right = _addition();
            auto node = GM_GC::alloc_args<GM_AST_VAR_EXPR>(token->m_word);
            node->add_childs(2, add, right);
            add = node;
        }

        return add;
    }

    GM_AST_TREE* GM_Parser::_addition()
    {
        auto mul = _multiplication();

        while (_match(GM_PLUS) || _match(GM_MINUS))
        {
            auto token = _peek(-1);
            auto right = _multiplication();
            auto node = GM_GC::alloc_args<GM_AST_VAR_EXPR>(token->m_word);
            node->add_childs(2, mul, right);
            mul = node;
        }

        return mul;
    }

    GM_AST_TREE* GM_Parser::_multiplication()
    {
        auto unary = _unary();

        while (_match(GM_STAR) || _match(GM_SLASH))
        {
            auto token = _peek(-1);
            auto right = _unary();
            auto node = GM_GC::alloc_args<GM_AST_VAR_EXPR>(token->m_word);
            node->add_childs(2, unary, right);
            unary = node;
        }

        return unary;
    }

    GM_AST_TREE* GM_Parser::_unary()
    {
        return _primary();
    }

    GM_AST_TREE* GM_Parser::_primary()
    {
        if (_match(GM_FALSE))
            return nullptr;

        if (_match(GM_TRUE))
            return nullptr;

        if (_match(GM_NULL))
            return GM_GC::alloc_args<GM_AST_NULL_EXPR>("null");
        
        if (_match(GM_NUMBER))
            return GM_GC::alloc_args<GM_AST_NUMBER_LITERAL_EXPR>(_peek(-1)->m_word, true);

        if (_match(GM_STRING))
            return GM_GC::alloc_args<GM_AST_STR_LITERAL_EXPR>(_peek(-1)->m_word);

        if (_match(GM_LEFT_PAREN))
        {
            auto expr = _expr();
            if (!_match(GM_RIGHT_PAREN))
            {
                // error
            }
            return expr;
        }

        return nullptr;
    }

    GM_AST_TREE* GM_Parser::_assignment_expr()
    {
        auto assign = GM_GC::alloc_args<GM_AST_VAR_EXPR>("let");

        // consume "var"
        if (!_match(GM_VAR))
        {
            // error
        }

        // variable identifier
        auto identifier = _IDENTIFIER();

        // consume "="
        if (!_match(GM_EQ))
        {
            // error
        }

        // arithmetic expression
        auto arithmetic_expr = _arithmetic_expr();

        assign->add_childs(2, identifier, arithmetic_expr);

        return assign;
    }

    GM_AST_TREE* GM_Parser::_IDENTIFIER()
    {
        if (!_check(GM_IDENTIFIER))
            return nullptr;
        const auto word = _advance()->m_word;
        return GM_GC::alloc_args<GM_AST_VAR_EXPR>(word);
    }

    GM_AST_TREE* GM_Parser::_STRING()
    {
        if (!_check(GM_STRING))
            return nullptr;
        const auto word = _advance()->m_word;
        return GM_GC::alloc_args<GM_AST_STR_LITERAL_EXPR>(word);
    }

    GM_AST_TREE* GM_Parser::_NUMBER()
    {
        if (!_check(GM_NUMBER))
            return nullptr;
        const auto word = _advance()->m_word;
        return GM_GC::alloc_args<GM_AST_NUMBER_LITERAL_EXPR>(word, true);
    }

    bool GM_Parser::_match(const GM_TokenType& type)
    {
        if (_check(type))
        {
            _advance();
            return true;
        }

        return false;
    }

    bool GM_Parser::_check(const GM_TokenType& type)
    {
        if (_is_end()) return false;
        return _peek()->m_type == type;
    }

    bool GM_Parser::_is_end()
    {
        return m_tokens == nullptr ? true : m_curt_idx >= m_tokens->size();
    }

    GM_Token* GM_Parser::_peek(const size_t& offset)
    {
        return (*m_tokens)[m_curt_idx + offset];
    }

    GM_Token* GM_Parser::_advance()
    {
        m_curt_idx++;
        return (*m_tokens)[m_curt_idx - 1];
    }

}
