#include "gm_token.hpp"
#include "GM.h"

namespace GM
{
    GM_Token::GM_Token(const GM_TokenType& type, const std::string& word, const size_t& line)
        : m_type(type), m_word(word), m_line(line)
    {
    }

    std::string GM_Token::str() const
    {
#ifdef DEBUG
        return GM_Utils::format_str("[<class '%s', type: %d, word: %s, line: %zu>, refcnt: %" PRIu64 ", insidx: %" PRIu64 "]",
            "token",
            m_type,
            m_word.c_str(),
            m_line,
            GCREFCNF(this),
            GCINSIDX(this));
#else
        return "<class 'token'>";
#endif
    }

}
