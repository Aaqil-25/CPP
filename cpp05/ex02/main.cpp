#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "===== Test 1: Shrubbery (sign 145, exec 137) =====" << std::endl;
	{
		Bureaucrat gardener("Gardener", 130);
		ShrubberyCreationForm shrub("garden");
		gardener.signForm(shrub);
		gardener.executeForm(shrub);
	}

	std::cout << "\n===== Test 2: execute before signing =====" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		RobotomyRequestForm robo("Bender");
		boss.executeForm(robo);
	}

	std::cout << "\n===== Test 3: Robotomy (sign 72, exec 45) =====" << std::endl;
	{
		Bureaucrat engineer("Engineer", 1);
		RobotomyRequestForm robo("Bender");
		engineer.signForm(robo);
		engineer.executeForm(robo);
		engineer.executeForm(robo);
	}

	std::cout << "\n===== Test 4: grade too low to execute =====" << std::endl;
	{
		Bureaucrat clerk("Clerk", 50);
		PresidentialPardonForm pardon("Marvin");
		Bureaucrat president("President", 1);
		president.signForm(pardon);
		clerk.executeForm(pardon);
	}

	std::cout << "\n===== Test 5: Presidential pardon (sign 25, exec 5) =====" << std::endl;
	{
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Marvin");
		president.signForm(pardon);
		president.executeForm(pardon);
	}

	std::cout << std::endl;
	return 0;
}
