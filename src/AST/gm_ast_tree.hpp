#pragma once

#include "../GM.h"

#include <vector>
#include <string>

namespace GM
{

    class GM_AST_TREE : extends(GM_Object)
    {
    public:
        GM_AST_TREE (std::string& token): m_token(token) {}
        ~GM_AST_TREE () override {};

    public:
        virtual size_t get_need_child_count() const = 0;

        static bool check_token_valid(std::string& token) { return false; };

        GM_AST_TREE* get_child(const int& index) const
        {
            if (m_childs == nullptr)
                return nullptr;

            return m_childs->at(index);
        }

        size_t get_child_count() const
        {
            if (m_childs == nullptr)
                return 0;

            return m_childs->size();
        }

        std::vector<GM_AST_TREE*>* get_childs() const { return m_childs; }

        void add_child(GM_AST_TREE* child) const { m_childs->push_back(child); }

    protected:
        std::vector<GM_AST_TREE*>* m_childs;
        std::string m_token;
    };

}