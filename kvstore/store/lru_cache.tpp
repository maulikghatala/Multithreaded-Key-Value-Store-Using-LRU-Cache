// #ifndef LRU_CACHE_TPP
// #define LRU_CACHE_TPP

// #include "lru_cache.hpp"

// template <typename K, typename V>
// bool LRUCache<K,V>::get(const K& key, V& value){
//     lock_guard<mutex>lock(mutex_);

//     auto it = item_map_.find(key);
//     if(it == item_map_.end()) return false;

//     item_list_.splice(item_list_.begin(), item_list_, it->second);
//     value = it->second->second;
//     return true;
// }

// template<typename K, typename V>
// void LRUCache<K, V>::put(const K& key, const V& value){
//     lock_guard<mutex>lock(mutex_);

//     auto it = item_map_.find(key);
//     if(it  != item_map_.end()){
//         item_list_.erase(it->second);
//         item_map_.erase(it);
//     }

//     item_list_.emplace_front(key, value);
//     item_map_[key] = item_list_.begin();

    
//     if (item_map_.size() > capacity_) {
//         auto last = item_list_.end();
//         --last;
//         item_map_.erase(last->first);
//         item_list_.pop_back();
//     }
// }


// #endif
