#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
	std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(const Intern& other)
{
	std::cout << "Intern copy constructor called" << std::endl;
	(void)other;
}

Intern& Intern::operator=(const Intern& other)
{
	std::cout << "Intern copy assignment operator called" << std::endl;
	(void)other;
	return *this;
}

Intern::~Intern()
{
	std::cout << "Intern destructor called" << std::endl;
}

AForm* Intern::makeShrubbery(std::string const & target)
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::makeRobotomy(std::string const & target)
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::makePresidential(std::string const & target)
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(std::string const & formName, std::string const & target)
{
	std::string const	names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	AForm* (*builders[3])(std::string const &) = {
		&Intern::makeShrubbery,
		&Intern::makeRobotomy,
		&Intern::makePresidential
	};

	for (int i = 0; i < 3; i++)
	{
		if (names[i] == formName)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return builders[i](target);
		}
	}
	std::cout << "Error: form \"" << formName << "\" does not exist." << std::endl;
	throw Intern::FormNotFoundException();
}

const char* Intern::FormNotFoundException::what() const throw()
{
	return "Requested form does not exist";
}
