#include "lru.hpp"

int main()
{
    int maxSize = 0;
    std::cout << "Input max size: ";
    std::cin >> maxSize;

    int maxVolume = 0;
    std::cout << "Input max volume: ";
    std::cin >> maxVolume;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    runLRU(std::cin, std::cout, maxSize, maxVolume);

    return 0;
}