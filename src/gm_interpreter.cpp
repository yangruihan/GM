#include "gm_interpreter.hpp"
#include "GM.h"

#define CHECK_TOKEN(func) \
do { \
ret = GM_InterpreterUtils::func(token); \
if (ret != nullptr) \
    return ret;     \
} while(0)

#define C_ENV get_current_data()->m_environment
#define C_PARSE_CURSOR get_current_data()->m_parse_cursor
#define C_TOKEN_INDEX get_current_data()->m_current_token_index
#define C_AST_ROOT get_current_data()->m_ast_root
#define C_TOKEN_INDEX_STACK get_current_data()->m_token_index_stack
#define C_PARSE_MODE get_current_data()->m_parse_mode


namespace GM
{

    GM_Interpreter::GM_Interpreter()
    {
        init();
    }
    
    GM_Interpreter::~GM_Interpreter() 
    {
        while (m_data_stack->size() > 0)
        {
            auto top = m_data_stack->top();
            m_data_stack->pop();
            delete top;
        }

        delete m_data_stack;
        delete m_global_environment;

        for (size_t i = 0, count = m_loaded_env->size(); i < count; i++)
        {
            delete (*m_loaded_env)[i];
        }
        delete m_loaded_env;
    }

    GM_Interpreter* GM_Interpreter::s_ins = new GM_Interpreter();

    GM_Interpreter* GM_Interpreter::instance()
    {
        return s_ins;
    }

    void GM_Interpreter::destory()
    {
        delete s_ins;
    }

    bool GM_Interpreter::init()
    {
        auto ret = true;

        m_global_environment = GM_Environment::create(nullptr);
        m_global_environment->set_var(GM_INTERPRETER_RUN_FLAG,
                                         GM_Value::bool_value(m_global_environment, true));

        ret = GM_BuiltinFunc::init(m_global_environment);
        if (!ret)
            return false;

        m_loaded_env = new std::vector<GM_Environment*>();

        m_data_stack = new std::stack<GM_Interpreter::GM_InterpreterData*>();

        return ret;
    }

    bool GM_Interpreter::_create_data(const size_t &parse_mode)
    {
        GM_Interpreter::GM_InterpreterData* data;
        auto ret = GM_Interpreter::GM_InterpreterData::create(data,
                                                              m_global_environment,
                                                              parse_mode);

        m_data_stack->push(data);

        return ret;
    }

    bool GM_Interpreter::_clear_data() const
    {
        m_loaded_env->push_back(C_ENV);
        auto data = get_current_data();
        m_data_stack->pop();
        delete data;

        return true;
    }

    bool GM_Interpreter::get_running_flag() const
    {
        auto flag = C_ENV->get_var(GM_INTERPRETER_RUN_FLAG);
        return dynamic_cast<GM_BoolValue*>(flag)->get_value();
    }

    int GM_Interpreter::repl()
    {
        _create_data(GM_INTERPRETER_REPL_MODE);

        std::string command;
        int ret = 0;
        bool running_flag = true;
        while (ret == 0 && running_flag)
        {
            std::cout << "> ";
            std::getline(std::cin, command);

            DEBUG_LOG_F("-- Input: %s", command.c_str());

            ret = parse_and_eval(command);

            running_flag = get_running_flag();
        }

        _clear_data();

        return ret;
    }

    int GM_Interpreter::parse_file(const std::string &file_path)
    {
        _create_data(GM_INTERPRETER_FILE_MODE);

        int ret = 0;
        if (GM_Utils::str_ends_with(file_path, GM_SOURCE_FILE_SUFFIX))
        {
            std::string file_content;
            if (GM_Utils::read_file(file_path.c_str(), file_content))
            {
                DEBUG_LOG_F("File: %s\n%s",
                            file_path.c_str(),
                            file_content.c_str());

                ret = parse_and_eval(file_content);
            }
            else
            {
                ret = -1;
                PRINT_ERROR_F("IOError: file(%s) read failed", file_path.c_str());
            }
        }

        _clear_data();

        return ret;
    }

    int GM_Interpreter::parse_and_eval(const std::string& command)
    {
        C_PARSE_CURSOR = 0;

        auto command_len = command.size();
        auto ret = 0;

        while (C_PARSE_CURSOR < command_len - 1)
        {
            ret = this->parse(command);

            if (ret == 0)
            {
#ifdef DEBUG
                DEBUG_LOG_F("Create AST success");
                DEBUG_LOG_F("--- Show AST structure ---");
                auto root = this->get_ast_root();
                this->_print_ast(root, 0);
                std::cout << std::endl;
#endif

                auto result = this->eval();
                if (result != nullptr)
                {
                    ret = 0;

#ifdef DEBUG
                    DEBUG_LOG_F("--------------------");
                    DEBUG_LOG_F("- Expr: %s", command.c_str());
                    DEBUG_LOG_F("- Result: %s", result->str().c_str());
                    DEBUG_LOG_F("--------------------");
#else
                    if (C_PARSE_MODE == GM_INTERPRETER_REPL_MODE)
                        std::cout << result->str().c_str() << std::endl;
#endif
                }
                else
                {
                    ret = -1;
                }
            }
            else
            {
                std::cout << "Error Code: " << ret << std::endl;
                break;
            }
        }

        return ret;
    }

    GM_Value* GM_Interpreter::eval() const
    {
        auto root = get_ast_root();
        
        if (root != nullptr)
        {
            return root->eval();
        }

        PRINT_ERROR("NullptrError: ast root is nullptr");
        return nullptr;
    }

    int GM_Interpreter::parse(const std::string& command)
    {
        C_TOKEN_INDEX = 0;

        C_AST_ROOT = _parse(command, C_ENV);

        if (C_AST_ROOT == nullptr)
            return -1;

        return 0;
    }

    GM_AST_TREE* GM_Interpreter::_parse(const std::string& command,
                                        GM_Environment* env)
    {
        if (C_PARSE_CURSOR >= command.size())
            return nullptr;

        GM_AST_TREE* ret = nullptr;
        std::string token;
        if (_take_token(command, token))
        {
            DEBUG_LOG_F("Get Token %s (%zu, %zu)",
                        token.c_str(),
                        C_TOKEN_INDEX_STACK->size(),
                        C_TOKEN_INDEX);

            ret = _get_ast_tree_from_token(token);

            if (ret == nullptr)
            {
                // TODO invalid
            }
            else
            {
                // set token index for AST Node
                ret->set_token_index(C_TOKEN_INDEX);

                if (command[C_PARSE_CURSOR - 1] == ')')
                {
                    C_TOKEN_INDEX = C_TOKEN_INDEX_STACK->top();
                    C_TOKEN_INDEX_STACK->pop();
                }
                else
                {
                    C_TOKEN_INDEX ++;
                }

                auto new_env = ret->set_environment(env);

                DEBUG_LOG_F("Create AST Node %s, child count %zu",
                            ret->get_token().c_str(),
                            ret->get_need_child_count());

                auto child_count = ret->get_need_child_count();

                auto parentheses_count = C_TOKEN_INDEX_STACK->size();
                auto command_len = command.size();

                if (command[C_PARSE_CURSOR - 1] == ')')
                {
                    if (child_count != GM_AST_VARIADIC_PARAMS_FLAG && child_count > 0)
                    {
                        PRINT_ERROR_F("SyntaxError: %s need %zu child but no one found",
                                      ret->str().c_str(),
                                      child_count);
                        return nullptr;
                    }

                    return ret;
                }

                // variadic parameter
                if (child_count == GM_AST_VARIADIC_PARAMS_FLAG)
                {
                    if (ret->get_token_index() == 0)
                    {
                        while (C_PARSE_CURSOR < command_len
                               && C_TOKEN_INDEX_STACK->size() >= parentheses_count)
                        {
                            auto child = _parse(command, new_env);
                            if (child == nullptr)
                                return nullptr;

                            if (!ret->add_child(child))
                                return nullptr;

                            while (command[C_PARSE_CURSOR] == ')'
                                   || GM_Utils::is_space(command[C_PARSE_CURSOR]))
                            {
                                if (command[C_PARSE_CURSOR] == ')')
                                {
                                    C_TOKEN_INDEX = C_TOKEN_INDEX_STACK->top();
                                    C_TOKEN_INDEX_STACK->pop();
                                }

                                C_PARSE_CURSOR++;
                            }
                        }
                    }
                }
                // fixed parameter
                else
                {
                    for (size_t i = 0; i < child_count; i++)
                    {
                        auto child = _parse(command, new_env);
                        if (child == nullptr)
                            return nullptr;

                        if (!ret->add_child(child))
                            return nullptr;
                    }

                    while (command[C_PARSE_CURSOR] == ')'
                           || GM_Utils::is_space(command[C_PARSE_CURSOR]))
                    {
                        if (command[C_PARSE_CURSOR] == ')')
                        {
                            C_TOKEN_INDEX = C_TOKEN_INDEX_STACK->top();
                            C_TOKEN_INDEX_STACK->pop();
                        }

                        C_PARSE_CURSOR++;
                    }
                }
            }
        }

        return ret;
    }

    GM_AST_TREE* GM_Interpreter::_get_ast_tree_from_token(const std::string& token) const
    {
        auto token_size = token.size();
        if (token_size == 0 || token[0] == ' ')
            return new GM_AST_NULL_EXPR("");

        GM_AST_TREE* ret;
        
        if (token_size == 1)
        {
            CHECK_TOKEN(check_token_is_operator);
        }

        // digit
        CHECK_TOKEN(check_token_is_number_literal);
        
        // str
        CHECK_TOKEN(check_token_is_str_literal);

        // list
        CHECK_TOKEN(check_token_is_list);

        // dict
        CHECK_TOKEN(check_token_is_dict);

        // variable
        CHECK_TOKEN(check_token_is_variable);

        PRINT_ERROR_F("SyntaxError: token(%s) is error", token.c_str());
        return nullptr;
    }

    bool GM_Interpreter::_take_token(const std::string& command, std::string& token)
    {
        auto command_len = command.size();
        if (command_len == 0)
        {
            DEBUG_ERROR("Command is empty");
            return false;
        }

        auto start_pos = C_PARSE_CURSOR;
        auto end_pos = C_PARSE_CURSOR;
        
        auto left_parentheses = false;
        auto quotation_mark = false;
        
        char c;
        while (end_pos < command_len)
        {
            c = command[end_pos];
            if (c == '\0')
            {
                if (left_parentheses)
                {
                    PRINT_ERROR("Syntax Error: no matching right parenthesis");
                    C_PARSE_CURSOR = command_len;
                    return false;
                }
                else
                {
                    token = command.substr(start_pos, end_pos - start_pos);
                    DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, end_pos);
                    C_PARSE_CURSOR = end_pos + 1;
                    return true;
                }
            }
            else if (c == '(')
            {
                if (left_parentheses)
                {
                    PRINT_ERROR("Syntax Error: double left parenthesis");
                    C_PARSE_CURSOR = command_len;
                    return false;
                }
                else
                {
                    C_TOKEN_INDEX_STACK->push(C_TOKEN_INDEX);
                    C_TOKEN_INDEX = 0;

                    left_parentheses = true;
                    start_pos++;
                    end_pos++;
                    continue;
                }
            }
            else if (c == ')')
            {
                if (C_TOKEN_INDEX_STACK->size() == 0)
                {
                    PRINT_ERROR("Syntax Error: no matching left parenthesis");
                    C_PARSE_CURSOR = command_len;
                    return false;
                }

                if (command[end_pos - 1] == '(')
                {
                    C_PARSE_CURSOR = end_pos + 1;
                    token = "";
                    return true;
                }
                else if (end_pos == start_pos)
                {
                    start_pos++;
                    end_pos++;
                    continue;
                }

                token = command.substr(start_pos, end_pos - start_pos);
                DEBUG_LOG_F("%s sub (%ld, %ld) -> %s",
                            command.c_str(),
                            start_pos,
                            end_pos,
                            token.c_str());

                C_PARSE_CURSOR = end_pos + 1;
                return true;
            }
            else if (GM_Utils::is_space(c))
            {
                if (end_pos == start_pos)
                {
                    start_pos++;
                    end_pos++;
                    continue;
                }

                if (!quotation_mark)
                {
                    token = command.substr(start_pos, end_pos - start_pos);
                    DEBUG_LOG_F("%s sub (%ld, %ld)", command.c_str(), start_pos, end_pos);
                    C_PARSE_CURSOR = end_pos + 1;
                    return true;
                }
            }
            else if (c == '"')
            {
                quotation_mark = !quotation_mark;
            }

            end_pos++;
        }

        return false;
    }

    GM_Value* GM_Interpreter::get_var_from_loaded_env(const std::string &var_name)
    {
        for (size_t i = 0, count = m_loaded_env->size(); i < count; i++)
        {
            auto env = (*m_loaded_env)[i];
            auto value = env->get_var(var_name, false);
            if (value != nullptr)
                return value;
        }

        return nullptr;
    }

    // ----- GM_InterpreterData ----- //
    bool GM_Interpreter::GM_InterpreterData::create(GM_Interpreter::GM_InterpreterData*& instance,
                                                    GM_Environment* env,
                                                    const size_t& parse_mode)
    {
        instance = new GM_Interpreter::GM_InterpreterData();
        instance->m_environment = GM_Environment::create(env);
        instance->m_parse_mode = parse_mode;

        return true;
    }

#ifdef DEBUG

    void GM_Interpreter::_print_ast(GM_AST_TREE* node, int indent) const
    {
        if (node == nullptr)
        {
            DEBUG_ERROR("node is nullptr");
            return;
        }

        std::cout << std::endl;

        for (size_t i = 0; i < indent; i++)
        {
            std::cout << "\t";
        }

        std::cout << node->str();

        for (size_t i = 0; i < node->get_child_count(); i++)
        {
            _print_ast(node->get_child(i), indent + 1);
        }
    }

#endif

}
