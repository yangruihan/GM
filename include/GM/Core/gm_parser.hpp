#pragma once

#include "gm_common_header.h"
#include "../Token/gm_token.hpp"

#include <vector>

namespace GM
{
    
    class GM_Token;
    class GM_AST_TREE;

    class GM_Parser : extends(GM_Object)
    {

    public:
        GM_Parser();
        ~GM_Parser() override = default;

        GM_AST_TREE* parse(const std::vector<GM_Token*>* tokens);

    private:
        GM_AST_TREE* _expr();
        
        GM_AST_TREE* _assignment_expr();

        GM_AST_TREE* _arithmetic_expr();
        GM_AST_TREE* _equality();
        GM_AST_TREE* _comparison();
        GM_AST_TREE* _addition();
        GM_AST_TREE* _multiplication();
        GM_AST_TREE* _unary();

        GM_AST_TREE* _primary();

        GM_AST_TREE* _IDENTIFIER();
        GM_AST_TREE* _NUMBER();
        GM_AST_TREE* _STRING();

        bool _match(const GM_TokenType& type);
        bool _check(const GM_TokenType& type);
        bool _is_end();

        GM_Token* _peek(const size_t& offset = 0);
        GM_Token* _advance();

    protected:
        std::vector<GM_Token*>* m_tokens;
        size_t                  m_curt_idx;

    };

}