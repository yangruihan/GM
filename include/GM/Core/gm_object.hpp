#pragma once

#include <string>

namespace GM
{

    class GM_Object
    {

    public:
        GM_Object ();
        virtual ~GM_Object ();

        virtual std::string str() const;

    };

}
