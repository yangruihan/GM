#include "gm_ast_list_expr.hpp"

#include "GM.h"
#include <sstream>

namespace GM
{

    GM_AST_LIST_EXPR::GM_AST_LIST_EXPR(const std::string& token)
                                        : GM_AST_TREE(token)
    {}
    
    GM_AST_LIST_EXPR::~GM_AST_LIST_EXPR()
    {
        GM_GC::free(m_environment);
    }

    size_t GM_AST_LIST_EXPR::get_need_child_count() const
    {
        return GM_AST_VARIADIC_PARAMS_FLAG;
    }

    bool GM_AST_LIST_EXPR::check_token_valid(const std::string& token)
    {
        if (token.size() == 2 && token == "[]")
            return true;

        if (token[0] != 'l' || token.size() !=4)
            return false;

        return token == "list";
    }

    GM_Value* GM_AST_LIST_EXPR::eval()
    {
        auto list_value = GM_Value::list_value(get_environment());
        for (size_t i = 0, count = get_child_count(); i < count; i++)
        {
            list_value->add_item(get_child(i)->eval());
        }
        return list_value;
    }

    std::string GM_AST_LIST_EXPR::token_list_str() const
    {
        std::ostringstream stream;
        stream << "(";
        for (size_t i = 0, count = get_child_count() - 1; i < count; i++)
        {
            stream << get_child(i)->get_token() << ", ";
        }
        stream << get_child(get_child_count() - 1)->get_token() << ")";

        return stream.str();
    }

    GM_Environment* GM_AST_LIST_EXPR::before_set_environment(GM_Environment* env)
    {
        return GM_Environment::create(env);
    }

    bool GM_AST_LIST_EXPR::_check_childs_valid() const
    {
        return true;
    }
}
