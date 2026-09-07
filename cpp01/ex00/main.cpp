#include "Zombie.hpp"
#include <iostream>

int main(void) {
    std::cout << "=== randomChump (stack) ===" << std::endl;
    randomChump("HeapHater");

    std::cout << "\n=== newZombie (heap) ===" << std::endl;
    Zombie* heapZombie = newZombie("HeapLover");
    heapZombie->announce();

    std::cout << "\n=== deleting heap zombie ===" << std::endl;
    delete heapZombie;
    heapZombie = NULL;

    return 0;
}
