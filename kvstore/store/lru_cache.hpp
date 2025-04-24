// #ifndef LRU_CACHE_HPP
// #define LRU_CACHE_HPP

// #include<list>
// #include<unordered_map>
// #include<mutex>
// #include<iostream>
// using namespace std;



// template<typename K, typename V>

// class LRUCache{
// public:
//     LRUCache(size_t capacity);
//     bool get(const K& key, V& value);
//     void put(const K& key, const V& value);

// private:
//     size_t capacity_;
//     list<pair<K, V>> item_list_;
//     unordered_map<K, typename list<pair<K, V>>::iterator> item_map_;
//     mutex mutex_;
// };

// #include "lru_cache.tpp"

// #endif




#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <list>
#include <unordered_map>
#include <mutex>

template<typename K, typename V>
class LRUCache {
public:
    LRUCache(size_t capacity) : capacity_(capacity) {}

    bool get(const K& key, V& value) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = item_map_.find(key);
        if (it == item_map_.end()) return false;

        item_list_.splice(item_list_.begin(), item_list_, it->second);
        value = it->second->second;
        return true;
    }

    void put(const K& key, const V& value) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = item_map_.find(key);
        if (it != item_map_.end()) {
            item_list_.erase(it->second);
            item_map_.erase(it);
        }

        item_list_.emplace_front(key, value);
        item_map_[key] = item_list_.begin();

        if (item_map_.size() > capacity_) {
            auto last = item_list_.end();
            --last;
            item_map_.erase(last->first);
            item_list_.pop_back();
        }
    }

private:
    size_t capacity_;
    std::list<std::pair<K, V>> item_list_;
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> item_map_;
    std::mutex mutex_;
};

#endif // LRU_CACHE_HPP
