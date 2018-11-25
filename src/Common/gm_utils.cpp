#include "gm_utils.hpp"

#include <string>
#include <stack>
#include <sstream>
#include <fstream>
#include "GM.h"

namespace GM
{

    GM_Environment* GM_Utils::set_env_for_childs(GM_AST_TREE* tree, GM_Environment* parent)
    {
        // create a new environment
        const auto new_env = GM_Environment::create(parent);

        // change env for func body
        tree->set_environment(new_env);
        std::stack<GM_AST_TREE*> stack;
        for (size_t i = 0, count = tree->get_child_count(); i < count; i++)
            stack.push(tree->get_child(i));

        while (!stack.empty())
        {
            auto ast_tree = stack.top();
            stack.pop();
            ast_tree->set_environment(new_env);

            for (size_t i = 0, count = ast_tree->get_child_count(); i < count; i++)
                stack.push(ast_tree->get_child(i));
        }

        return new_env;
    }

    GM_Value* GM_Utils::get_last_value(GM_Value *value)
    {
        auto list_value = dynamic_cast<GM_ListValue*>(value);
        if (list_value == nullptr)
            return value;

        return (*list_value)[list_value->get_item_count() - 1];
    }

    std::string GM_Utils::vector_str(const std::vector<GM_Object*>* vector)
    {
        if (vector == nullptr)
            return "[vector is nullptr]";

        std::ostringstream stream;
        stream << "[";
        auto count = vector->size() - 1;
        for (size_t i = 0; i < count; i++)
        {
            stream << (*vector)[i]->str() << ", ";
        }
        stream << (*vector)[count]->str() << "]";
        return stream.str();
    }

    std::string GM_Utils::dict_str(const std::map<std::string, GM_Object *> *dict)
    {
        if (dict == nullptr)
            return "{dict is nullptr}";

        std::ostringstream stream;
        stream << "{";
        for (auto it = dict->begin(); it != dict->end(); it++)
        {
            stream << '\"' << it->first << '\"' << ": " << it->second << std::endl;
        }
        stream << "}";
        return stream.str();
    }

    bool GM_Utils::is_empty_or_all_space(const std::string& str)
    {
        if (str == "")
            return true;

        for (size_t i = 0, count = str.size(); i < count; i++)
        {
            if (!is_space(str[i]))
                return false;
        }

        return true;
    }

    bool GM_Utils::str_ends_with(const std::string& full_str, const std::string& ends)
    {
        if (full_str.length() >= ends.length())
            return (0 == full_str.compare (full_str.length() - ends.length(), ends.length(), ends));
        else
            return false;
    }

    bool GM_Utils::read_file(const char* file_path, std::string& content)
    {
        std::ifstream file(file_path);
        content = "";
        if (file.is_open())
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            content = buffer.str();
            return true;
        }

        return false;
    }

    bool GM_Utils::write_file(const char* file_path, const std::string& content)
    {
        std::ofstream file (file_path);
        if (file.is_open())
        {
            file << content;
            file.close();
            return true;
        }

        return false;
    }

}
