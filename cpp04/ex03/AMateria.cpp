#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria() : type("")
{
	std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(std::string const & type) : type(type)
{
	std::cout << "AMateria constructor called for type: " << type << std::endl;
}

AMateria::AMateria(const AMateria& other) : type(other.type)
{
	std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria& AMateria::operator=(const AMateria& other)
{
	std::cout << "AMateria copy assignment operator called" << std::endl;
	(void)other;
	// The type is intentionally NOT copied: an Ice stays an Ice.
	return *this;
}

AMateria::~AMateria()
{
	std::cout << "AMateria destructor called" << std::endl;
}

std::string const & AMateria::getType() const
{
	return this->type;
}

void AMateria::use(ICharacter& target)
{
	(void)target;
	std::cout << "* uses a generic materia *" << std::endl;
}
