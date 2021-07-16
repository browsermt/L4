#pragma once

#include <cstdint>
#include <limits>

namespace L4 {

// EpochRefPolicy class
template <typename EpochRefManager>
class EpochRefPolicy {
 public:
  explicit EpochRefPolicy(EpochRefManager& epochRefManager)
      : m_epochRefManager{epochRefManager},
        m_epochCounter{m_epochRefManager.AddRef()} {}

  EpochRefPolicy(EpochRefPolicy&& epochRefPolicy)
      : m_epochRefManager{epochRefPolicy.m_epochRefManager},
        m_epochCounter{epochRefPolicy.m_epochCounter} {
    epochRefPolicy.m_epochCounter =
        std::numeric_limits<std::uint64_t>::max();
  }

  ~EpochRefPolicy() {
    if (m_epochCounter != std::numeric_limits<std::uint64_t>::max()) {
      m_epochRefManager.RemoveRef(m_epochCounter);
    }
  }

  EpochRefPolicy(const EpochRefPolicy&) = delete;
  EpochRefPolicy& operator=(const EpochRefPolicy&) = delete;

 private:
  EpochRefManager& m_epochRefManager;
  std::uint64_t m_epochCounter;
};

}  // namespace L4
