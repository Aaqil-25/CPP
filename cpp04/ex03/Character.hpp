#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <string>

class Character : public ICharacter
{
	private:
		std::string	name;
		AMateria*	inventory[4];

		// Materias dropped on the floor by unequip(); kept here so we can
		// delete them at destruction and avoid memory leaks.
		AMateria**	floor;
		int			floorSize;
		int			floorCapacity;

		void		dropOnFloor(AMateria* m);

	public:
		Character();
		Character(std::string const & name);
		Character(const Character& other);
		Character& operator=(const Character& other);
		virtual ~Character();

		virtual std::string const & getName() const;
		virtual void equip(AMateria* m);
		virtual void unequip(int idx);
		virtual void use(int idx, ICharacter& target);
};

#endif
