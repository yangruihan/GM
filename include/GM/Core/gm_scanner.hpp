#pragma once

#include "gm_common_header.h"
#include "gm_token.hpp"

#include <string>
#include <vector>
#include <map>

namespace GM
{

    class GM_Scanner : extends(GM_Object)
    {
    public:
        GM_Scanner(const std::string& source);
        ~GM_Scanner() override = default;

        std::vector<GM_Token*> scan_tokens();

    protected:
        void _scan_token();

        void _add_token(const GM_TokenType& type);
        void _add_token(const GM_TokenType& type,
                       const std::string& word);

        void _string_token();
        void _number_token();
        void _identifier_token();

        char _advance();
        char _peek(const size_t& offset=0);

        bool _is_end();

    protected:
        std::string            m_source;
        std::vector<GM_Token*> m_tokens;
        size_t                 m_source_len;
        size_t                 m_start_pos;
        size_t                 m_curt_pos;
        size_t                 m_line;
        std::map<std::string, GM_TokenType> m_id_map;
    };

}
