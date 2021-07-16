#pragma once

#include <optional>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <memory>
#include "HashTable/IHashTable.h"
#include "Utils/Properties.h"

namespace L4 {

// HashTableConfig struct.
struct HashTableConfig {
  struct Setting {
    using KeySize = IReadOnlyHashTable::Key::size_type;
    using ValueSize = IReadOnlyHashTable::Value::size_type;

    explicit Setting(std::uint32_t numBuckets,
                     std::optional<std::uint32_t> numBucketsPerMutex = {},
                     std::optional<KeySize> fixedKeySize = {},
                     std::optional<ValueSize> fixedValueSize = {})
        : m_numBuckets{numBuckets},
          m_numBucketsPerMutex{numBucketsPerMutex},
          m_fixedKeySize{fixedKeySize},
          m_fixedValueSize{fixedValueSize} {}

    std::uint32_t m_numBuckets;
    std::optional<std::uint32_t> m_numBucketsPerMutex;
    std::optional<KeySize> m_fixedKeySize;
    std::optional<ValueSize> m_fixedValueSize;
  };

  struct Cache {
    Cache(std::uint64_t maxCacheSizeInBytes,
          std::chrono::seconds recordTimeToLive,
          bool forceTimeBasedEviction)
        : m_maxCacheSizeInBytes{maxCacheSizeInBytes},
          m_recordTimeToLive{recordTimeToLive},
          m_forceTimeBasedEviction{forceTimeBasedEviction} {}

    std::uint64_t m_maxCacheSizeInBytes;
    std::chrono::seconds m_recordTimeToLive;
    bool m_forceTimeBasedEviction;
  };

  struct Serializer {
    using Properties = Utils::Properties;

    Serializer(std::shared_ptr<std::istream> stream = {},
               std::optional<Properties> properties = {})
        : m_stream{stream}, m_properties{properties} {}

    std::shared_ptr<std::istream> m_stream;
    std::optional<Properties> m_properties;
  };

  HashTableConfig(std::string name,
                  Setting setting,
                  std::optional<Cache> cache = {},
                  std::optional<Serializer> serializer = {})
      : m_name{std::move(name)},
        m_setting{std::move(setting)},
        m_cache{cache},
        m_serializer{serializer} {
    assert(m_setting.m_numBuckets > 0U ||
           (m_serializer && (serializer->m_stream != nullptr)));
  }

  std::string m_name;
  Setting m_setting;
  std::optional<Cache> m_cache;
  std::optional<Serializer> m_serializer;
};

}  // namespace L4
