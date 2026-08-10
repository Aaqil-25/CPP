#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	std::cout << "===== Subject test =====" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j; // should not create a leak
	delete i;

	std::cout << "\n===== Array of Animals (half Dog, half Cat) =====" << std::endl;
	const int size = 6;
	Animal* animals[size];

	for (int k = 0; k < size; k++)
	{
		if (k < size / 2)
			animals[k] = new Dog();
		else
			animals[k] = new Cat();
	}

	std::cout << "\n----- makeSound of each -----" << std::endl;
	for (int k = 0; k < size; k++)
		animals[k]->makeSound();

	std::cout << "\n----- delete every Animal -----" << std::endl;
	for (int k = 0; k < size; k++)
		delete animals[k];

	std::cout << "\n===== Deep copy test (copy constructor) =====" << std::endl;
	Dog original;
	original.getBrain()->setIdea(0, "I want a bone");

	Dog copy(original);
	std::cout << "original idea 0: " << original.getBrain()->getIdea(0) << std::endl;
	std::cout << "copy idea 0:     " << copy.getBrain()->getIdea(0) << std::endl;

	copy.getBrain()->setIdea(0, "I changed my mind");
	std::cout << "after modifying the copy:" << std::endl;
	std::cout << "original idea 0: " << original.getBrain()->getIdea(0) << std::endl;
	std::cout << "copy idea 0:     " << copy.getBrain()->getIdea(0) << std::endl;
	std::cout << "brain addresses differ: "
			  << (original.getBrain() != copy.getBrain() ? "yes" : "no") << std::endl;

	std::cout << "\n===== Deep copy test (assignment operator) =====" << std::endl;
	Cat a;
	Cat b;
	a.getBrain()->setIdea(5, "fish");
	b = a;
	b.getBrain()->setIdea(5, "milk");
	std::cout << "a idea 5: " << a.getBrain()->getIdea(5) << std::endl;
	std::cout << "b idea 5: " << b.getBrain()->getIdea(5) << std::endl;

	std::cout << "\n===== End of scope destructors =====" << std::endl;
	return 0;
}
