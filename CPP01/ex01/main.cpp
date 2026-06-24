#include "Zombie.hpp"
#include <iostream>

int main(void) {
    std::cout << "=== Creating a horde of 5 zombies ===" << std::endl;
    int N = 5;
    Zombie* horde = zombieHorde(N, "Soldier");

    for (int i = 0; i < N; i++)
        horde[i].announce();

    std::cout << "\n=== Destroying the horde ===" << std::endl;
    delete[] horde;
    horde = NULL;

    std::cout << "\n=== Creating a horde of 3 zombies ===" << std::endl;
    N = 3;
    horde = zombieHorde(N, "Walker");

    for (int i = 0; i < N; i++)
        horde[i].announce();

    std::cout << "\n=== Destroying the horde ===" << std::endl;
    delete[] horde;
    horde = NULL;

    return 0;
}
