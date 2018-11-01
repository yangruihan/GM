#pragma once

#include "../GM.h"

#include <vector>

namespace GM
{

    class GM_AST_TREE : extends(GM_Object)
    {
    public:
        GM_AST_TREE () {}
        virtual ~GM_AST_TREE () = 0;

    public:
        virtual int parse(char* command, int& start_pos) = 0;

        GM_AST_TREE* get_child(int& index)
        {
            if (m_childs == nullptr)
                return nullptr;

            return m_childs->at(index);
        }

        int get_child_count()
        {
            if (m_childs == nullptr)
                return 0;

            return m_childs->size();
        }

        std::vector<GM_AST_TREE*>* get_childs() { return m_childs; }

    protected:
        std::vector<GM_AST_TREE*>* m_childs;
    };

}