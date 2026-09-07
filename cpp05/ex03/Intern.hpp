#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <iostream>
#include <exception>

class AForm;

class Intern
{
	private:
		static AForm*	makeShrubbery(std::string const & target);
		static AForm*	makeRobotomy(std::string const & target);
		static AForm*	makePresidential(std::string const & target);

	public:
		Intern();
		Intern(const Intern& other);
		Intern& operator=(const Intern& other);
		~Intern();

		AForm*	makeForm(std::string const & formName, std::string const & target);

		class FormNotFoundException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif
