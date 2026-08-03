#include "ScavTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== Construction chaining ===" << std::endl;
	ScavTrap scav("Serena");

	std::cout << "\n=== Actions ===" << std::endl;
	scav.attack("Intruder");
	scav.takeDamage(30);
	scav.beRepaired(10);
	scav.guardGate();

	std::cout << "\n=== Orthodox Canonical Form ===" << std::endl;
	ScavTrap copy(scav);
	ScavTrap assigned;
	assigned = scav;

	std::cout << "\n=== Destruction chaining (reverse order) ===" << std::endl;
	return 0;
}
