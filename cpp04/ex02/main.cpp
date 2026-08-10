#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	// The following line must NOT compile because Animal is now abstract:
	// Animal* meta = new Animal();   // <-- uncomment to see the compile error

	std::cout << "===== Concrete animals still work =====" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << j->getType() << std::endl;
	std::cout << i->getType() << std::endl;

	j->makeSound();
	i->makeSound();

	delete j;
	delete i;

	std::cout << "\n===== Array of Animals (half Dog, half Cat) =====" << std::endl;
	const int size = 4;
	Animal* animals[size];

	for (int k = 0; k < size; k++)
	{
		if (k < size / 2)
			animals[k] = new Dog();
		else
			animals[k] = new Cat();
	}

	for (int k = 0; k < size; k++)
		animals[k]->makeSound();

	for (int k = 0; k < size; k++)
		delete animals[k];

	return 0;
}
