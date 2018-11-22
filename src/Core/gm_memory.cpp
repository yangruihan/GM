#include "gm_memory.hpp"
#include "GM.h"

namespace GM
{

    GM_MemoryManager* GM_MemoryManager::s_ins;

    GM_GarbageCollector* GM_GarbageCollector::s_ins;

    uint64_t GM_GarbageCollector::s_ins_idx_counter = GM_DEFAULT_INS_IDX_START;

}
