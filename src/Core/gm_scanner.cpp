#include "gm_scanner.hpp"

#include "GM.h"

namespace GM
{

    GM_Scanner::GM_Scanner(const std::string& source)
    : m_source(source), m_source_len(source.size()),
      m_start_pos(0), m_curt_pos(0), m_line(1)
    {
        m_id_map["and"]     = GM_AND;
        m_id_map["or"]      = GM_OR;
        m_id_map["if"]      = GM_IF;
        m_id_map["else"]    = GM_ELSE;
        m_id_map["true"]    = GM_TRUE;
        m_id_map["false"]   = GM_FALSE;
        m_id_map["for"]     = GM_FOR;
        m_id_map["while"]   = GM_WHILE;
        m_id_map["return"]  = GM_RETURN;
        m_id_map["fn"]      = GM_FN;
        m_id_map["null"]    = GM_NULL;
        m_id_map["var"]     = GM_VAR;
        m_id_map["class"]   = GM_CLASS;
        m_id_map["super"]   = GM_SUPER;
        m_id_map["this"]    = GM_THIS;
    }

    std::vector<GM_Token*> GM_Scanner::scan_tokens()
    {
        while (!_is_end()) {
            m_start_pos = m_curt_pos;
            _scan_token();
        }

        _add_token(GM_EOF, "");
        return m_tokens;
    }

    void GM_Scanner::_scan_token()
    {
        char c = _advance();
        switch (c)
        {
            // ignore char
            case ' ':
            case '\r':
            case '\t':
                break;

            case '\n':
                m_line++;
                break;

            case '(':
                _add_token(GM_LEFT_PAREN);
                break;

            case ')':
                _add_token(GM_RIGHT_PAREN);
                break;

            case '{':
                _add_token(GM_LEFT_BRACE);
                break;

            case '}':
                _add_token(GM_RIGHT_BRACE);
                break;

            case ',':
                _add_token(GM_COMMA);
                break;

            case '.':
                _add_token(GM_DOT);
                break;

            case '-':
                _add_token(GM_MINUS);
                break;

            case '+':
                _add_token(GM_PLUS);
                break;

            case ';':
                _add_token(GM_SEMICOLON);
                break;

            case '*':
                _add_token(GM_STAR);
                break;

            case '!':
                if (_peek() == '=')
                { _advance(); _add_token(GM_BANG_EQ); }
                else
                { _add_token(GM_BANG); }
                break;

            case '=':
                if (_peek() == '=')
                { _advance(); _add_token(GM_DOUBLE_EQ); }
                else
                { _add_token(GM_EQ); }
                break;

            case '>':
                if (_peek() == '=')
                { _advance(); _add_token(GM_GREATER_EQ); }
                else
                { _add_token(GM_GREATER); }
                break;

            case '<':
                if (_peek() == '=')
                { _advance(); _add_token(GM_LESS_EQ); }
                else
                { _add_token(GM_LESS); }
                break;

            case '/':
                // commnets
                if (_peek() == '/')
                {
                    _advance();
                    while (_peek() != '\n' && !_is_end())
                        _advance();
                }
                else
                    _add_token(GM_SLASH);
                break;

            case '"':
                _string_token();
                break;

            default:
                if (GM_Utils::is_digit(c))
                    _number_token();
                else if (GM_Utils::is_alpha(c) || c == '_')
                    _identifier_token();
                else
                    error(m_line, "Unexpected character");
                break;
        }
    }

    void GM_Scanner::_string_token()
    {
        while (_peek() != '"' and !_is_end())
        {
            if (_peek() == '\n') m_line++;
            _advance();
        }

        if (_is_end())
        {
            error(m_line, "Untermiated string");
            return;
        }

        _advance();

        std::string content = m_source.substr(m_start_pos + 1,
                                              m_curt_pos - m_start_pos - 2);
        _add_token(GM_STRING, content);
    }

    void GM_Scanner::_number_token()
    {
        while (GM_Utils::is_digit(_peek()))
            _advance();

        if (_peek() == '.' && GM_Utils::is_digit(_peek(1)))
        {
            _advance();
            while (GM_Utils::is_digit(_peek()))
                _advance();
        }

        _add_token(GM_NUMBER);
    }

    void GM_Scanner::_identifier_token()
    {
        char c = _peek();

        while (GM_Utils::is_alpha_or_num(c) || c == '_')
        {
            _advance();
            c = _peek();
        }

        std::string id = m_source.substr(m_start_pos, m_curt_pos - m_start_pos);

        auto it = m_id_map.find(id);
        if (it != m_id_map.end())
            _add_token(m_id_map[id], id);
        else
            _add_token(GM_IDENTIFIER, id);
    }

    void GM_Scanner::_add_token(const GM::GM_TokenType& type)
    {
        std::string word = m_source.substr(m_start_pos,
                                           m_curt_pos - m_start_pos);
        _add_token(type, word);
    }

    void GM_Scanner::_add_token(const GM::GM_TokenType &type,
                               const std::string &word)
    {
        m_tokens.push_back(new GM_Token(type, word, m_line));
    }

    char GM_Scanner::_advance()
    {
        m_curt_pos++;
        return m_source[m_curt_pos - 1];
    }

    char GM_Scanner::_peek(const size_t &offset)
    {
        if (m_curt_pos + offset >= m_source_len)
            return '\0';
        return m_source[m_curt_pos + offset];
    }

    bool GM_Scanner::_is_end()
    {
        return m_curt_pos >= m_source_len;
    }

}
