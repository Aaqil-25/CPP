#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== FragTrap construction chaining ===" << std::endl;
	FragTrap frag("Fraggy");

	std::cout << "\n=== FragTrap actions ===" << std::endl;
	frag.attack("Enemy");
	frag.takeDamage(40);
	frag.beRepaired(20);
	frag.highFivesGuys();

	std::cout << "\n=== ScavTrap still works ===" << std::endl;
	ScavTrap scav("Serena");
	scav.guardGate();

	std::cout << "\n=== Orthodox Canonical Form ===" << std::endl;
	FragTrap copy(frag);
	FragTrap assigned;
	assigned = frag;

	std::cout << "\n=== Destruction chaining (reverse order) ===" << std::endl;
	return 0;
}
