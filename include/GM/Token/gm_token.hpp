#pragma once

#include "gm_common_header.h"

#include <string>

namespace GM
{

    enum GM_TokenType
    {

        GM_LEFT_PAREN   = 0,  // (
        GM_RIGHT_PAREN  = 1,  // )
        GM_LEFT_BRACE   = 2,  // {
        GM_RIGHT_BRACE  = 3,  // }
        GM_COMMA        = 4,  // ,
        GM_DOT          = 5,  // .
        GM_MINUS        = 6,  // -
        GM_PLUS         = 7,  // +
        GM_SEMICOLON    = 8,  // ;
        GM_SLASH        = 9,  // /
        GM_STAR         = 10, // *

        GM_BANG         = 11, // !
        GM_BANG_EQ      = 12, // !=
        GM_EQ           = 13, // =
        GM_DOUBLE_EQ    = 14, // ==
        GM_GREATER      = 15, // >
        GM_GREATER_EQ   = 16, // >=
        GM_LESS         = 17, // <
        GM_LESS_EQ      = 18, // <=

        GM_STRING       = 19, // string
        GM_NUMBER       = 20, // number
        GM_IDENTIFIER   = 21, // identifier

        GM_AND          = 22, // and
        GM_OR           = 23, // or
        GM_IF           = 24, // if
        GM_ELSE         = 25, // else
        GM_TRUE         = 26, // true
        GM_FALSE        = 27, // false
        GM_FOR          = 28, // for
        GM_WHILE        = 29, // while
        GM_RETURN       = 30, // return
        GM_FN           = 31, // fn
        GM_NULL         = 32, // null
        GM_VAR          = 33, // var

        GM_CLASS        = 34, // class
        GM_SUPER        = 35, // super
        GM_THIS         = 36, // this

        GM_EOF          = 37, // end of file
        
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
