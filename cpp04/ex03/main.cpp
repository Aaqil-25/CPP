#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"

int main()
{
	std::cout << "===== Subject test =====" << std::endl;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;

	std::cout << "\n===== Unknown type returns 0 =====" << std::endl;
	MateriaSource* src2 = new MateriaSource();
	src2->learnMateria(new Ice());
	AMateria* unknown = src2->createMateria("fire");
	std::cout << "createMateria(\"fire\") returned: "
			  << (unknown == 0 ? "0 (NULL)" : "a materia") << std::endl;
	delete unknown;
	delete src2;

	std::cout << "\n===== Deep copy of Character =====" << std::endl;
	MateriaSource* source = new MateriaSource();
	source->learnMateria(new Ice());
	source->learnMateria(new Cure());

	Character* alice = new Character("alice");
	alice->equip(source->createMateria("ice"));
	alice->equip(source->createMateria("cure"));

	Character* clone = new Character(*alice); // deep copy
	Character* target = new Character("target");

	std::cout << "alice uses slot 0 on target:" << std::endl;
	alice->use(0, *target);
	std::cout << "clone uses slot 0 on target:" << std::endl;
	clone->use(0, *target);

	delete alice; // deleting alice must not affect clone (deep copy)
	std::cout << "after deleting alice, clone still works:" << std::endl;
	clone->use(1, *target);

	delete clone;
	delete target;
	delete source;

	std::cout << "\n===== unequip does not delete + full inventory =====" << std::endl;
	MateriaSource* s = new MateriaSource();
	s->learnMateria(new Ice());
	Character* hero = new Character("hero");
	hero->equip(s->createMateria("ice"));
	hero->equip(s->createMateria("ice"));
	hero->equip(s->createMateria("ice"));
	hero->equip(s->createMateria("ice"));
	AMateria* overflow = s->createMateria("ice");
	hero->equip(overflow);   // 5th: inventory full, nothing happens
	delete overflow;         // caller still owns it, so we free it ourselves
	hero->unequip(0); // dropped on the floor (not deleted, no leak)
	hero->use(0, *hero); // slot 0 empty now: nothing happens
	hero->use(1, *hero); // still works

	delete hero; // floor materia is cleaned up here
	delete s;

	return 0;
}
