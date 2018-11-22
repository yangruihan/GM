#pragma once

#include <vector>
#include <string>

#include "../Core/gm_common_header.h"
#include "../Type/gm_value.hpp"
#include "../Core/gm_environment.hpp"

namespace GM
{
    class GM_AST_BINARY_EXPR;
    class GM_AST_DICT_EXPR;
    class GM_AST_LIST_EXPR;
    class GM_AST_LITERAL_EXPR;
    class GM_AST_ADD_OPERATOR_EXPR;
    class GM_AST_SUB_OPERATOR_EXPR;
    class GM_AST_MUL_OPERATOR_EXPR;
    class GM_AST_DIV_OPERATOR_EXPR;
    class GM_AST_NULL_EXPR;
    class GM_AST_STR_LITERAL_EXPR;
    class GM_AST_VAR_EXPR;

    class GM_AST_TREE : extends(GM_Object)
    {
    protected:
        GM_AST_TREE (const std::string& token): m_token(token)
        {
            m_childs = new std::vector<GM_AST_TREE*>();
        }

        ~GM_AST_TREE () override
        {
            for (size_t i = 0, count = get_child_count(); i < count; i++)
                delete (*m_childs)[i];

            delete m_childs;
        }

        friend class GM_MemoryManager;
        friend class GM_GarbageCollector;

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
            return m_environment;
        }
        
        GM_Environment* get_environment()
        { return before_get_environment(); }
    
    protected:
        virtual bool _check_childs_valid() const = 0;
        
        /* --- environment --- */
        virtual GM_Environment* before_set_environment(GM_Environment* env)
        { return env; }
        
        virtual GM_Environment* before_get_environment()
        { return m_environment; }

    protected:
        std::vector<GM_AST_TREE*>* m_childs;

        const std::string m_token;

        size_t m_token_index;
        
        GM_Environment* m_environment;
    };

}
