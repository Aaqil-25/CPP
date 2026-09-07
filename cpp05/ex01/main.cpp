#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "===== Test 1: high-grade bureaucrat signs an easy form =====" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 1);
		Form taxes("Taxes", 50, 25);
		std::cout << taxes << std::endl;
		alice.signForm(taxes);
		std::cout << taxes << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== Test 2: low-grade bureaucrat can't sign =====" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 100);
		Form contract("Contract", 50, 25);
		bob.signForm(contract);
		std::cout << contract << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== Test 3: creating a form with an invalid grade =====" << std::endl;
	try
	{
		Form broken("Broken", 0, 25);
		std::cout << broken << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== Test 4: bureaucrat exactly at required grade =====" << std::endl;
	try
	{
		Bureaucrat carol("Carol", 50);
		Form permit("Permit", 50, 25);
		carol.signForm(permit);
		std::cout << permit << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	return 0;
}
