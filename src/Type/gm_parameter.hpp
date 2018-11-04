#pragma

#include "../GM.h"
#include "gm_types_header.h"

namespace GM
{
    class GM_Parameter : extends(GM_Object)
    {
    public:
        GM_Parameter();
        virtual ~GM_Parameter();
        
    protected:
        GM_ListValue* m_list_params;
        GM_DictionaryValue* m_dic_params;
    };
}
