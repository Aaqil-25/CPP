#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	Intern someRandomIntern;

	std::cout << "\n===== Test 1: intern makes a robotomy request =====" << std::endl;
	{
		AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		Bureaucrat boss("Boss", 1);
		boss.signForm(*rrf);
		boss.executeForm(*rrf);
		delete rrf;
	}

	std::cout << "\n===== Test 2: intern makes a presidential pardon =====" << std::endl;
	{
		AForm* ppf = someRandomIntern.makeForm("presidential pardon", "Marvin");
		Bureaucrat president("President", 1);
		president.signForm(*ppf);
		president.executeForm(*ppf);
		delete ppf;
	}

	std::cout << "\n===== Test 3: intern makes a shrubbery creation =====" << std::endl;
	{
		AForm* scf = someRandomIntern.makeForm("shrubbery creation", "garden");
		Bureaucrat gardener("Gardener", 1);
		gardener.signForm(*scf);
		gardener.executeForm(*scf);
		delete scf;
	}

	std::cout << "\n===== Test 4: intern asked for an unknown form =====" << std::endl;
	try
	{
		AForm* unknown = someRandomIntern.makeForm("coffee machine", "kitchen");
		delete unknown;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	return 0;
}
