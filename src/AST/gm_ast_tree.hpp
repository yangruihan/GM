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
        /* --- token --- */
        static bool check_token_valid(std::string& token) { return false; };

        std::string get_token() const { return m_token; }

        /* --- child --- */
        virtual size_t get_need_child_count() const = 0;

        GM_AST_TREE* get_child(const int& index) const
        {
            if (m_childs == nullptr)
            {
                PRINT_ERROR("NullptrError: childs is nullptr");
                return nullptr;
            }

            if (index < 0 || index > m_childs->size())
            {
                PRINT_ERROR_F("IndexError: out of range(%d)", m_childs->size());
                return nullptr;
            }

            return m_childs->at(index);
        }

        size_t get_child_count() const
        {
            if (m_childs == nullptr)
                return 0;

            return m_childs->size();
        }

        std::vector<GM_AST_TREE*>* get_childs() const { return m_childs; }

        void add_child(GM_AST_TREE* child) 
        { 
            if (m_childs == nullptr)
                m_childs = new std::vector<GM_AST_TREE*>();

            DEBUG_ERROR_F("--- %s add child %s", 
                                m_token.c_str(),
                                child->get_token().c_str());

            m_childs->push_back(child); 
        }

    protected:
        std::vector<GM_AST_TREE*>* m_childs;
        std::string m_token;
    };

}