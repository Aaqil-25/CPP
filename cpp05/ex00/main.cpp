#include "Bureaucrat.hpp"

int main()
{
	std::cout << "===== Test 1: valid bureaucrat =====" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 2);
		std::cout << alice << std::endl;
		alice.incrementGrade();
		std::cout << "After increment: " << alice << std::endl;
		alice.incrementGrade();
		std::cout << "After increment: " << alice << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== Test 2: grade too high at construction =====" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 0);
		std::cout << boss << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== Test 3: grade too low at construction =====" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 151);
		std::cout << intern << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== Test 4: incrementing past grade 1 =====" << std::endl;
	try
	{
		Bureaucrat top("Top", 1);
		std::cout << top << std::endl;
		top.incrementGrade();
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n===== Test 5: decrementing past grade 150 =====" << std::endl;
	try
	{
		Bureaucrat bottom("Bottom", 150);
		std::cout << bottom << std::endl;
		bottom.decrementGrade();
	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	return 0;
}
