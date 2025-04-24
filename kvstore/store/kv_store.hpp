#ifndef KV_STORE_HPP
#define KV_STORE_HPP

#include <string>
#include <optional>
#include "lru_cache.hpp"



class KVStore {
public:
    KVStore(size_t capacity);

    std::optional<std::string> get(const std::string& key);
    void put(const std::string& key, const std::string& value);
    void remove(const std::string& key);

private:
    LRUCache<std::string, std::string> cache_;
};

#endif // KV_STORE_HPP
