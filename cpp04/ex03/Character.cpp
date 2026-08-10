#include "Character.hpp"

Character::Character() : name("default"), floor(0), floorSize(0), floorCapacity(0)
{
	std::cout << "Character default constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
		this->inventory[i] = 0;
}

Character::Character(std::string const & name)
	: name(name), floor(0), floorSize(0), floorCapacity(0)
{
	std::cout << "Character constructor called for: " << name << std::endl;
	for (int i = 0; i < 4; i++)
		this->inventory[i] = 0;
}

Character::Character(const Character& other)
	: ICharacter(), floor(0), floorSize(0), floorCapacity(0)
{
	std::cout << "Character copy constructor called" << std::endl;
	this->name = other.name;
	for (int i = 0; i < 4; i++)
	{
		if (other.inventory[i])
			this->inventory[i] = other.inventory[i]->clone();
		else
			this->inventory[i] = 0;
	}
}

Character& Character::operator=(const Character& other)
{
	std::cout << "Character copy assignment operator called" << std::endl;
	if (this != &other)
	{
		this->name = other.name;
		for (int i = 0; i < 4; i++)
		{
			delete this->inventory[i];
			this->inventory[i] = 0;
		}
		for (int i = 0; i < 4; i++)
		{
			if (other.inventory[i])
				this->inventory[i] = other.inventory[i]->clone();
		}
	}
	return *this;
}

Character::~Character()
{
	std::cout << "Character destructor called for: " << this->name << std::endl;
	for (int i = 0; i < 4; i++)
		delete this->inventory[i];
	for (int i = 0; i < this->floorSize; i++)
		delete this->floor[i];
	delete [] this->floor;
}

void Character::dropOnFloor(AMateria* m)
{
	if (this->floorSize == this->floorCapacity)
	{
		int newCap = (this->floorCapacity == 0) ? 4 : this->floorCapacity * 2;
		AMateria** newFloor = new AMateria*[newCap];
		for (int i = 0; i < this->floorSize; i++)
			newFloor[i] = this->floor[i];
		delete [] this->floor;
		this->floor = newFloor;
		this->floorCapacity = newCap;
	}
	this->floor[this->floorSize] = m;
	this->floorSize++;
}

std::string const & Character::getName() const
{
	return this->name;
}

void Character::equip(AMateria* m)
{
	if (!m)
		return;
	for (int i = 0; i < 4; i++)
	{
		if (this->inventory[i] == 0)
		{
			this->inventory[i] = m;
			return;
		}
	}
	// Inventory is full: nothing happens (materia is left with the caller).
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4 || this->inventory[idx] == 0)
		return;
	// Do NOT delete: keep the pointer on the floor so it is not leaked.
	this->dropOnFloor(this->inventory[idx]);
	this->inventory[idx] = 0;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= 4 || this->inventory[idx] == 0)
		return;
	this->inventory[idx]->use(target);
}
