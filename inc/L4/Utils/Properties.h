#pragma once

#include "Utils/Containers.h"


namespace L4 {
namespace Utils {

// Properties class represents a string to string map (case insensitive).
// It can be used where the configurations should be generic.
class Properties : public StdStringKeyMap<std::string> {
 public:
  using Base = Utils::StdStringKeyMap<std::string>;
  using Value = Base::value_type;

  Properties() = default;

  // Expose a constructor with initializer_list for convenience.
  Properties(std::initializer_list<Value> values) : Base(values) {}

};

}  // namespace Utils
}  // namespace L4
