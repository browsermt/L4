#pragma once

// #include <boost/interprocess/containers/vector.hpp>
#include <vector>

namespace L4 {
namespace Interprocess {
namespace Container {

// template <typename T, typename Allocator>
// using Vector = boost::interprocess::vector<T, Allocator>;
// @jerinphilip: This is probably a bad idea.
template <typename T, typename Allocator>
using Vector = std::vector<T, Allocator>;

}  // namespace Container
}  // namespace Interprocess
}  // namespace L4
