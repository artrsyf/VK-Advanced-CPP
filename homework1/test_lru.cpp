#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "lru.hpp"

void testPutAndGet()
{
    LRUCache<std::string, std::string> cache(3, 100);

    assert(cache.put("key1", "value1", 10));
    std::string value;
    assert(cache.get("key1", value) && value == "value1");

    assert(cache.put("key1", "value2", 15));
    assert(cache.get("key1", value) && value == "value2");
}

void testEvictionBySize()
{
    LRUCache<std::string, std::string> cache(3, 50);

    assert(cache.put("key1", "value1", 20));
    assert(cache.put("key2", "value2", 20));

    assert(!cache.put("key3", "value3", 60));

    std::string value;
    assert(cache.get("key1", value) && value == "value1");
    assert(cache.get("key2", value) && value == "value2");

    assert(cache.put("key3", "value3", 15));
    assert(cache.get("key3", value) && value == "value3");
    assert(!cache.get("key1", value));
}

void testEvictionByCount()
{
    LRUCache<std::string, std::string> cache(2, 100);

    assert(cache.put("key1", "value1", 10));
    assert(cache.put("key2", "value2", 10));

    assert(cache.put("key3", "value3", 10));

    std::string value;
    assert(!cache.get("key1", value));
    assert(cache.get("key2", value) && value == "value2");
    assert(cache.get("key3", value) && value == "value3");
}

void testInvalidSize()
{
    LRUCache<std::string, std::string> cache(3, 100);

    assert(!cache.put("key1", "value1", 150));

    assert(cache.size() == 0);
}

void testAccessOrder()
{
    LRUCache<std::string, std::string> cache(3, 100);

    assert(cache.put("key1", "value1", 10));
    assert(cache.put("key2", "value2", 10));
    assert(cache.put("key3", "value3", 10));

    std::string value;
    assert(cache.get("key1", value) && value == "value1");

    assert(cache.put("key4", "value4", 10));
    assert(!cache.get("key2", value));
    assert(cache.get("key1", value) && value == "value1");
    assert(cache.get("key4", value) && value == "value4");
}

void testEmbeddingCache()
{
    std::istringstream input(
        "key1\t1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 "
        "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n"
        "key2\t1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 "
        "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n"
        "key3\t1 1 1 1 1 1 1 1 3 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 "
        "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n");
    std::ostringstream output;
    runLRU(input, output, 2, 128);

    assert(output.str().find("!STORERR!") != std::string::npos);
}

void testStoreAbility()
{
    std::string someEmbeddingValue = "1 1 1 1 1 1 1 2 3 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 "
                                     "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 3";
    std::ostringstream inputBuffer;
    inputBuffer << "some_key\t" << someEmbeddingValue << "\nsome_key\n";

    std::istringstream input(inputBuffer.str());
    std::ostringstream output;
    runLRU(input, output, 2, 400);

    assert(output.str() == "!STORED!\n" + someEmbeddingValue + " \n");
}

void testConstructorAndInstantiation()
{
    LRUCache<int, float> intFloatCache(5, 100);
    assert(intFloatCache.capacity() == 5);

    using MapValue = std::map<std::string, int>;
    LRUCache<std::string, MapValue> stringMapCache(3, 200);
    assert(stringMapCache.capacity() == 3);
}

void runTests()
{
    testPutAndGet();
    testEvictionBySize();
    testEvictionByCount();
    testInvalidSize();
    testAccessOrder();
    testEmbeddingCache();
    testConstructorAndInstantiation();
    testStoreAbility();

    std::cout << "All LRU tests passed!\n";
}

int main()
{
    runTests();

    return 0;
}
