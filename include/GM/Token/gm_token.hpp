#pragma once

#include "gm_common_header.h"

#include <string>

namespace GM
{

    enum GM_TokenType
    {

        GM_LEFT_PAREN,         // (
        GM_RIGHT_PAREN,        // )
        GM_LEFT_BRACE,         // {
        GM_RIGHT_BRACE,        // }
        GM_COMMA,              // ,
        GM_DOT,                // .
        GM_MINUS,              // -
        GM_PLUS,               // +
        GM_SEMICOLON,          // ;
        GM_SLASH,              // /
        GM_STAR,               // *

        GM_BANG,               // !
        GM_BANG_EQ,            // !=
        GM_EQ,                 // =
        GM_DOUBLE_EQ,          // ==
        GM_GREATER,            // >
        GM_GREATER_EQ,         // >=
        GM_LESS,               // <
        GM_LESS_EQ,            // <=

        GM_STRING,             // string
        GM_NUMBER,             // number
        GM_IDENTIFIER,         // identifier

        GM_AND,                // and
        GM_OR,                 // or
        GM_IF,                 // if
        GM_ELSE,               // else
        GM_TRUE,               // true
        GM_FALSE,              // false
        GM_FOR,                // for
        GM_WHILE,              // while
        GM_RETURN,             // return
        GM_FN,                 // fn
        GM_NULL,               // null
        GM_VAR,                // var

        GM_CLASS,              // class
        GM_SUPER,              // super
        GM_THIS,               // this

        GM_EOF,                // end of file
        
    };

    class GM_Token : extends(GM_Object)
    {
    public:
        GM_Token(const GM_TokenType& type, const std::string& word, const size_t& line);
        ~GM_Token() override = default;

        std::string str() const override;

    public:
        GM_TokenType m_type;
        std::string  m_word;
        size_t       m_line;
    };

}