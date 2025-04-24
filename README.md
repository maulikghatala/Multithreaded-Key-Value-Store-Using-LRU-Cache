# 🧠 Multithreaded Key-Value Store with LRU Cache

A simple C++11-based TCP key-value store with multithreading and an LRU cache to keep memory usage efficient. Inspired by Redis-style in-memory stores.

---

## 🚀 Features

- ✅ Thread-safe key-value store
- ✅ LRU (Least Recently Used) eviction policy
- ✅ TCP-based client-server communication
- ✅ Handles multiple clients concurrently using C++ threads

---

## 📦 Build Instructions

Make sure you have a C++ compiler (like `g++`) installed.

```bash
# Clone the repo and build
g++ -std=c++23 -pthread main.cpp server/tcp_server.cpp store/kv_store.cpp -o kvstore
