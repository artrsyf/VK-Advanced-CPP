#include <cassert>
#include <iostream>
#include <string>

#include "hashtable.hpp"

void testInsertAndFind()
{
    UnorderedMap<std::string, int> map;
    map.insert({ "one", 1 });
    map.insert({ "two", 2 });

    assert(map.size() == 2);
    assert(map["one"] == 1);
    assert(map["two"] == 2);
    assert(map.find("three") == map.end());
}

void testErase()
{
    UnorderedMap<std::string, int> map;
    map.insert({ "one", 1 });
    map.insert({ "two", 2 });
    map.insert({ "three", 3 });

    map.erase(map.find("one"));
    assert(map.size() == 2);
    assert(map.find("one") == map.end());

    map.erase(map.find("three"));
    assert(map.size() == 1);
    assert(map.find("three") == map.end());

    assert(!map.erase(map.find("four")));
}

void testClear()
{
    UnorderedMap<std::string, int> map;
    map.insert({ "one", 1 });
    map.insert({ "two", 2 });

    map.clear();
    assert(map.size() == 0);
    assert(map.empty());
}

void testResize()
{
    UnorderedMap<std::string, int> map;

    map.insert({ "one", 1 });
    map.insert({ "two", 2 });
    map.insert({ "three", 3 });

    map.reserve(10);
    assert(map.size() == 3);
}

void testLoadFactor()
{
    UnorderedMap<std::string, int> map;

    map.insert({ "one", 1 });
    map.insert({ "two", 2 });

    assert(map.load_factor() <= map.max_load_factor());
}

void testOperator()
{
    UnorderedMap<std::string, int> map;

    map["one"] = 1;
    map["two"] = 2;

    assert(map["one"] == 1);
    assert(map["two"] == 2);

    assert(map["three"] == 0);
}

void testReserveAndRehash()
{
    UnorderedMap<std::string, int> map;
    map.reserve(16);

    map.insert({ "one", 1 });
    map.insert({ "two", 2 });

    assert(map.size() == 2);
    assert(map.find("one") != map.end());
    assert(map.find("two") != map.end());
}

void runTests()
{
    testInsertAndFind();
    testErase();
    testClear();
    testResize();
    testLoadFactor();
    testOperator();
    testReserveAndRehash();

    std::cout << "All UnorderedMap tests passed!\n";
}

int main()
{
    runTests();

    return 0;
}
