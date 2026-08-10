#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	std::cout << "MateriaSource default constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
		this->templates[i] = 0;
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
	std::cout << "MateriaSource copy constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (other.templates[i])
			this->templates[i] = other.templates[i]->clone();
		else
			this->templates[i] = 0;
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	std::cout << "MateriaSource copy assignment operator called" << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < 4; i++)
		{
			delete this->templates[i];
			this->templates[i] = 0;
		}
		for (int i = 0; i < 4; i++)
		{
			if (other.templates[i])
				this->templates[i] = other.templates[i]->clone();
		}
	}
	return *this;
}

MateriaSource::~MateriaSource()
{
	std::cout << "MateriaSource destructor called" << std::endl;
	for (int i = 0; i < 4; i++)
		delete this->templates[i];
}

void MateriaSource::learnMateria(AMateria* m)
{
	if (!m)
		return;
	for (int i = 0; i < 4; i++)
	{
		if (this->templates[i] == 0)
		{
			this->templates[i] = m;
			return;
		}
	}
	// Cannot learn more than 4: delete the given materia to avoid a leak,
	// since learnMateria takes ownership of the pointer.
	delete m;
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->templates[i] && this->templates[i]->getType() == type)
			return this->templates[i]->clone();
	}
	return 0;
}
