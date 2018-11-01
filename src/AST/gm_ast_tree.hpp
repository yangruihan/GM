#pragma once

#include "../GM.h"

#include <vector>

namespace GM
{

    class GM_AST_TREE : extends(GM_Object)
    {
    public:
        GM_AST_TREE ();
        virtual ~GM_AST_TREE ();

    public:
        virtual GM_AST_TREE* get_child(int& index) = 0;
        virtual int get_child_count() = 0;
        
        std::vector<GM_AST_TREE*> get_childs() { return m_childs; }

    private:
        std::vector<GM_AST_TREE*> m_childs;
    };

}