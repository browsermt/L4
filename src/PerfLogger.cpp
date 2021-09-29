#include "Log/PerfCounter.h"
#include "Log/PerfLogger.h"
#include "Utils/Exception.h"
#include <sstream>

namespace L4 {

// PerfData class implementation.

void PerfData::AddHashTablePerfData(const char* hashTableName,
                                    const HashTablePerfData& perfData) {
  auto result = m_hashTablesPerfData.insert(
      std::make_pair(hashTableName, HashTablesPerfData::mapped_type(perfData)));

  if (!result.second) {
    std::stringstream stream;
    stream << "Duplicate hash table name found: ";
    stream << hashTableName;
    throw RuntimeException(stream.str());
  }
}

}  // namespace L4
