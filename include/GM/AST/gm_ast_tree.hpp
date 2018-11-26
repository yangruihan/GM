#pragma once

#include <vector>
#include <string>
#include <utility>

#include "../Core/gm_common_header.h"
#include "../Type/gm_value.hpp"
#include "../Core/gm_environment.hpp"
#include "gm_memory.hpp"

namespace GM
{

    KEEP_ENV
    class GM_AST_TREE : extends(GM_Object)
    {
    
    public:
        GM_AST_TREE (const std::string& token): m_token(token)
        {
            m_childs = new std::vector<GM_AST_TREE*>();
        }

        ~GM_AST_TREE () override
        {
            for (size_t i = 0, count = get_child_count(); i < count; i++)
                GCFREE((*m_childs)[i]);

            delete m_childs;

            GCFREE(m_environment);
        }

        GM_AST_TREE(const GM_AST_TREE& other) = delete;

    public:
        template<class T = GM_AST_TREE, class ...TArgs>
        static T* create(TArgs &&... args)
        {
            return GM_GC::alloc_args<T>(std::forward<TArgs>(args)...);
        }

    public:

        GM_AST_STR_FUNC(GM_AST_TREE)

        /* --- eval --- */
        virtual GM_Value* eval() = 0;

        /* --- token --- */
        static bool check_token_valid(std::string& token) { return false; }

        std::string get_token() const { return m_token; }

        void set_token_index(const size_t& token_index) { m_token_index = token_index; }

        size_t get_token_index() { return m_token_index; }

        /* --- child --- */
        virtual size_t get_need_child_count() const = 0;

        GM_AST_TREE* get_child(const int& index) const
        {
#ifdef DEBUG
            if (m_childs->empty())
            {
                PRINT_ERROR("NullptrError: childs is empty");
                return nullptr;
            }

            if (index < 0 || index > m_childs->size())
            {
                PRINT_ERROR_F("IndexError: out of range(%zu)", m_childs->size());
                return nullptr;
            }
#endif

            return (*m_childs)[index];
        }

        size_t get_child_count() const
        {
            if (m_childs == nullptr)
                return 0;

            return m_childs->size();
        }

        std::vector<GM_AST_TREE*>* get_childs() const { return m_childs; }

        bool add_child(GM_AST_TREE* child)
        {
            if (child == nullptr)
            {
                PRINT_ERROR_F("NullptrError: AST_NODE(%s) add child error, child is nullptr",
                              get_token().c_str());
                return false;
            }

            GCINC(child);
            m_childs->push_back(child);

            DEBUG_LOG_F("Current AST_NODE(%s) add child AST_NODE(%s)",
                        str().c_str(),
                        child->str().c_str());

            return true;
        }

        /* --- environment --- */
        GM_Environment* set_environment(GM_Environment* environment)
        {
            m_environment = before_set_environment(environment);
            GCINC(m_environment);
            return m_environment;
        }
        
        GM_Environment* get_environment() { return m_environment; }

        GM_Environment* get_environment() const { return m_environment; }
    
    protected:
        virtual bool _check_childs_valid() const = 0;
        
        /* --- environment --- */
        virtual GM_Environment* before_set_environment(GM_Environment* env)
        { return env; }

    protected:
        std::vector<GM_AST_TREE*>* m_childs;
        const std::string          m_token;
        size_t                     m_token_index;
        GM_Environment*            m_environment = nullptr;
    };

}
