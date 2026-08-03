#include "ClapTrap.hpp"
#include <iostream>

int	main(void)
{
	std::cout << "=== Construction ===" << std::endl;
	ClapTrap a("Alpha");
	ClapTrap b("Bravo");

	std::cout << "\n=== Attacks ===" << std::endl;
	a.attack("Bravo");
	b.attack("Alpha");

	std::cout << "\n=== Damage & Repair ===" << std::endl;
	a.takeDamage(5);
	a.beRepaired(3);
	a.takeDamage(20);
	a.attack("Bravo");
	a.beRepaired(5);

	std::cout << "\n=== Energy drain ===" << std::endl;
	ClapTrap c("Charlie");
	for (int i = 0; i < 11; i++)
		c.attack("Dummy");

	std::cout << "\n=== Orthodox Canonical Form ===" << std::endl;
	ClapTrap d(a);
	ClapTrap e;
	e = b;

	std::cout << "\n=== Destruction ===" << std::endl;
	return 0;
}
