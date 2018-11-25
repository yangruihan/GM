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

    private:
        friend class GM_MemoryManager;
        friend class GM_GarbageCollector;

        uint16_t m_memory_chunk_idx = 0;        // memory chunk index
        uint64_t m_ref_cnt          = 0;        // reference count
        uint64_t m_ins_idx          = 0;        // instance index

    };

}
