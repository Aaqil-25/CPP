#include "DiamondTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== DiamondTrap construction (ClapTrap once) ===" << std::endl;
	DiamondTrap diamond("Dia");

	std::cout << "\n=== whoAmI ===" << std::endl;
	diamond.whoAmI();

	std::cout << "\n=== Inherited abilities ===" << std::endl;
	diamond.attack("Target");
	diamond.takeDamage(25);
	diamond.beRepaired(10);
	diamond.guardGate();
	diamond.highFivesGuys();

	std::cout << "\n=== Orthodox Canonical Form ===" << std::endl;
	DiamondTrap copy(diamond);
	copy.whoAmI();
	DiamondTrap assigned;
	assigned = diamond;
	assigned.whoAmI();

	std::cout << "\n=== Destruction (reverse order) ===" << std::endl;
	return 0;
}
