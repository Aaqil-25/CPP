#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "===== Subject test =====" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	i->makeSound(); // will output the cat sound!
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;

	std::cout << "\n===== WrongAnimal test =====" << std::endl;
	const WrongAnimal* wmeta = new WrongAnimal();
	const WrongAnimal* wc = new WrongCat();

	std::cout << wc->getType() << " " << std::endl;

	wc->makeSound(); // outputs WrongAnimal sound (no virtual dispatch)
	wmeta->makeSound();

	delete wmeta;
	delete wc;

	std::cout << "\n===== Direct WrongCat test =====" << std::endl;
	WrongCat realWrongCat;
	realWrongCat.makeSound(); // outputs WrongCat sound (static type is WrongCat)

	std::cout << "\n===== Stack objects & polymorphism via reference =====" << std::endl;
	Dog dog;
	Cat cat;
	Animal& ref = dog;
	ref.makeSound(); // Dog sound thanks to virtual + reference

	return 0;
}
