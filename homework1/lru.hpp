#include <cassert>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "hashtable.hpp"

template<typename KeyT, typename ValueT, typename HashT = std::hash<KeyT>,
    typename ComparatorT = std::equal_to<KeyT>>
class LRUCache {
public:
    LRUCache(size_t maxItems, size_t maxSize)
        : maxItems(maxItems)
        , maxSize(maxSize)
        , currentSize(0)
    {
    }

    bool put(const KeyT& key, const ValueT& value, size_t size)
    {
        if (size > maxSize) {
            return false;
        }

        auto it = cache.find(key);
        if (it != cache.end()) {
            moveToFront(it->second);
            currentSize -= it->second.size;
            it->second.value = value;
            it->second.size = size;
            currentSize += size;
        } else {
            if (cache.size() >= maxItems || currentSize + size > maxSize) {
                evict(size);
            }

            auto listIt = accessOrder.emplace(accessOrder.begin(), key);
            cache[key] = { value, size, listIt };
            currentSize += size;
        }

        return true;
    }

    bool get(const KeyT& key, ValueT& value)
    {
        auto it = cache.find(key);
        if (it == cache.end())
            return false;
        moveToFront(it->second);
        value = it->second.value;
        return true;
    }

    size_t size() const { return cache.size(); }
    size_t capacity() const { return maxItems; }
    size_t currentMemoryUsage() const { return currentSize; }

private:
    struct CacheEntry {
        ValueT value;
        size_t size;
        typename std::list<KeyT>::iterator accessOrderIt;
    };

    size_t maxItems;
    size_t maxSize;
    size_t currentSize;
    // std::unordered_map<KeyT, CacheEntry, HashT, ComparatorT> cache;
    UnorderedMap<KeyT, CacheEntry, HashT, ComparatorT> cache;
    std::list<KeyT> accessOrder;

    void moveToFront(CacheEntry& entry)
    {
        accessOrder.erase(entry.accessOrderIt);
        entry.accessOrderIt = accessOrder.emplace(accessOrder.begin(), *(entry.accessOrderIt));
    }

    void evict(size_t newElementSize)
    {
        while (cache.size() > 0 && (cache.size() >= maxItems || currentSize + newElementSize > maxSize)) {
            auto oldestKey = accessOrder.back();
            auto it = cache.find(oldestKey);
            currentSize -= it->second.size;
            accessOrder.pop_back();
            cache.erase(it);
        }
    }
};

size_t calculateSize(const std::string& key, const std::vector<float>& value)
{
    return key.size() + value.size() * sizeof(float);
}

void runLRU(std::istream& input, std::ostream& output, size_t maxItems,
    size_t maxSize)
{
    LRUCache<std::string, std::vector<float>> cache(maxItems, maxSize);

    std::string inputString = "";
    while (std::getline(input, inputString) && !inputString.empty()) {
        std::istringstream iss(inputString);
        std::string key;
        iss >> key;

        if (iss.peek() == '\t') {
            iss.ignore();
            std::vector<float> embedding(64);
            for (float& f : embedding) {
                if ((iss >> f) && !f) {
                    output << "!STORERR!\n";
                    goto next;
                }
            }

            size_t size = calculateSize(key, embedding);
            if (cache.put(key, embedding, size)) {
                output << "!STORED!\n";
            } else {
                output << "!STORERR!\n";
            }
        } else {
            std::vector<float> embedding;
            if (cache.get(key, embedding)) {
                for (float f : embedding) {
                    output << f << " ";
                }
                output << "\n";
            } else {
                output << "!NOEMBED!\n";
            }
        }
    next:
        continue;
    }
}