#include <cassert>
#include <cmath>
#include <functional>
#include <list>
#include <stdexcept>
#include <vector>

#include <iostream>

template<typename Key, typename Value, typename HashT = std::hash<Key>,
    typename ComparatorT = std::equal_to<Key>>
class UnorderedMap {
public:
    using KeyValuePair = std::pair<Key, Value>;
    using Bucket = std::list<KeyValuePair>;

    UnorderedMap(size_t initial_capacity = 8, float max_load_factor = 0.75f)
        : table(initial_capacity)
        , hasher(HashT())
        , comparator(ComparatorT())
        , maxLoadFactor(max_load_factor)
        , elementCount(0)
    {
    }

    template<typename PairT>
    class GenericIterator {
    public:
        using TableIterator = typename std::vector<Bucket>::iterator;
        using BucketIterator = typename Bucket::iterator;

        GenericIterator(TableIterator tableIt, TableIterator tableEnd, BucketIterator bucketIt)
            : tableIt(tableIt)
            , tableEnd(tableEnd)
            , bucketIt(bucketIt)
        {
            advanceToNextValid();
        }

        PairT& operator*() { return *bucketIt; }
        PairT* operator->() { return &(*bucketIt); }

        GenericIterator& operator++()
        {
            ++bucketIt;
            advanceToNextValid();
            return *this;
        }

        bool operator==(const GenericIterator& other) const
        {
            return tableIt == other.tableIt && bucketIt == other.bucketIt;
        }

        bool operator!=(const GenericIterator& other) const { return !(*this == other); }

    private:
        TableIterator tableIt;
        TableIterator tableEnd;
        BucketIterator bucketIt;

        void advanceToNextValid()
        {
            while (tableIt != tableEnd && bucketIt == tableIt->end()) {
                ++tableIt;
                if (tableIt != tableEnd)
                    bucketIt = tableIt->begin();
            }
        }
    };

    using Iterator = GenericIterator<KeyValuePair>;
    using ConstIterator = GenericIterator<const KeyValuePair>;

    Iterator begin()
    {
        return Iterator(table.begin(), table.end(), table.front().begin());
    }

    Iterator end()
    {
        return Iterator(table.end(), table.end(), typename Bucket::iterator());
    }

    ConstIterator begin() const
    {
        return ConstIterator(table.begin(), table.end(), table.front().begin());
    }

    ConstIterator end() const
    {
        return ConstIterator(table.end(), table.end(), typename Bucket::const_iterator());
    }

    ConstIterator cbegin() const { return begin(); }
    ConstIterator cend() const { return end(); }

    size_t size() const { return elementCount; }
    bool empty() const { return elementCount == 0; }
    float load_factor() const
    {
        return static_cast<float>(elementCount) / table.size();
    }
    float max_load_factor() const { return maxLoadFactor; }
    void max_load_factor(float factor) { maxLoadFactor = factor; }

    void clear()
    {
        table.clear();
        table.resize(8);
        elementCount = 0;
    }

    void reserve(size_t newCapacity)
    {
        rehash(std::max(newCapacity, static_cast<size_t>(std::ceil(elementCount / maxLoadFactor))));
    }

    Value& operator[](const Key& key)
    {
        auto it = find(key);
        if (it != end())
            return it->second;
        auto bucketIndex = getBucketIndex(key);
        table[bucketIndex].emplace_back(key, Value());
        ++elementCount;
        checkRehash();
        return table[bucketIndex].back().second;
    }

    Iterator find(const Key& key)
    {
        size_t bucketIndex = getBucketIndex(key);
        auto& bucket = table[bucketIndex];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (comparator(it->first, key))
                return Iterator(table.begin() + bucketIndex, table.end(), it);
        }
        return end();
    }

    ConstIterator find(const Key& key) const
    {
        size_t bucketIndex = getBucketIndex(key);
        const auto& bucket = table[bucketIndex];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (comparator(it->first, key))
                return ConstIterator(table.begin() + bucketIndex, table.end(), it);
        }
        return end();
    }

    bool insert(const KeyValuePair& pair)
    {
        if (find(pair.first) != end())
            return false;
        size_t bucketIndex = getBucketIndex(pair.first);
        table[bucketIndex].push_back(pair);
        ++elementCount;
        checkRehash();
        return true;
    }

    bool erase(const Iterator& it)
    {
        if (it == end()) {
            return false;
        }

        auto nonConstItCopy = it;

        size_t bucketIndex = getBucketIndex(nonConstItCopy->first);
        auto& bucket = table[bucketIndex];

        auto iter = std::find_if(bucket.begin(), bucket.end(),
            [&nonConstItCopy](const KeyValuePair& pair) {
                return pair.first == nonConstItCopy->first;
            });

        if (iter != bucket.end()) {
            bucket.erase(iter);
            --elementCount;
            return true;
        }
        return false;
    }

private:
    std::vector<Bucket> table;
    HashT hasher;
    ComparatorT comparator;
    float maxLoadFactor;
    size_t elementCount;

    size_t getBucketIndex(const Key& key) const
    {
        return hasher(key) % table.size();
    }

    void checkRehash()
    {
        if (load_factor() > maxLoadFactor)
            rehash(2 * table.size());
    }

    void rehash(size_t newCapacity)
    {
        std::vector<Bucket> newTable(newCapacity);
        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                size_t newIndex = hasher(pair.first) % newCapacity;
                newTable[newIndex].push_back(std::move(pair));
            }
        }
        table.swap(newTable);
    }
};