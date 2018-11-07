#include "gm_ast_dict_expr.hpp"

#include "../GM.h"
#include <sstream>

namespace GM
{

    GM_AST_DICT_EXPR::GM_AST_DICT_EXPR(const std::string& token)
        : GM_AST_TREE(token)
    {}

    GM_AST_DICT_EXPR::~GM_AST_DICT_EXPR() {}

    size_t GM_AST_DICT_EXPR::get_need_child_count() const
    {
        return GM_AST_VARIADIC_PARAMS_FLAG;
    }

    bool GM_AST_DICT_EXPR::check_token_valid(const std::string &token)
    {
        if (token.size() == 2 && token == "{}")
            return true;

        if (token[0] != 'd' || token.size() != 4)
            return false;
        
        return token == "dict";
    }

    GM_Value* GM_AST_DICT_EXPR::eval()
    {
        auto dict_value = GM_Value::dict_value(get_environment());
        for (size_t i = 0, count = get_child_count(); i < count; i++)
        {
            auto pair_value = dynamic_cast<GM_PairValue*>(get_child(i)->eval());
            if (pair_value == nullptr)
            {
                PRINT_ERROR_F("TypeErro: %zus child is not a pair", i);
                return GM_Value::null_value();
            }
            dict_value->add_item(pair_value->get_key(), pair_value);
        }
        return dict_value;
    }

    GM_Environment* GM_AST_DICT_EXPR::before_set_environment(GM_Environment* env)
    {
        return GM_Environment::create(env);
    }

    bool GM_AST_DICT_EXPR::_check_childs_valid() const
    {
        return true;
    }
    
}
