#include "kv_store.hpp"


KVStore::KVStore(size_t capacity) : cache_(capacity) {}

std::optional<std::string> KVStore::get(const std::string& key) {
    std::string value;
    if (cache_.get(key, value)) {
        return value;
    }
    return std::nullopt;
}

void KVStore::put(const std::string& key, const std::string& value) {
    cache_.put(key, value);
}

// void KVStore::remove(const std::string& key) {
//     // Remove by overwriting with dummy/empty string (you could improve this later)
//     cache_.put(key, "");
// }


void KVStore::remove(const std::string& key) {
    // Dummy workaround since LRUCache doesn't support real deletion
    std::string dummy;
    if (cache_.get(key, dummy)) {
        cache_.put(key, "__DELETED__"); // Mark as deleted
    }
}

