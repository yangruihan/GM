#include "gm_memory.hpp"

namespace GM
{

    GM_MemoryManager* GM_MemoryManager::s_ins;

    GM_GarbageCollector* GM_GarbageCollector::s_ins;

    uint64_t GM_GarbageCollector::s_ins_idx_counter = 0x1000000000000000;

}
