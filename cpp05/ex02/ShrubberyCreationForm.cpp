#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), target("default")
{
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const & target)
	: AForm("ShrubberyCreationForm", 145, 137), target(target)
{
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), target(other.target)
{
	std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	std::cout << "ShrubberyCreationForm copy assignment operator called" << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
		this->target = other.target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

void ShrubberyCreationForm::executeAction() const
{
	std::ofstream outfile((this->target + "_shrubbery").c_str());

	if (!outfile.is_open())
	{
		std::cout << "Error: could not open file " << this->target
			<< "_shrubbery" << std::endl;
		return;
	}
	outfile << "       ###" << std::endl;
	outfile << "      #o###" << std::endl;
	outfile << "    #####o###" << std::endl;
	outfile << "   #o#\\#|#/###" << std::endl;
	outfile << "    ###\\|/#o#" << std::endl;
	outfile << "     # }|{  #" << std::endl;
	outfile << "       }|{" << std::endl;
	outfile << std::endl;
	outfile << "       ###" << std::endl;
	outfile << "      #o###" << std::endl;
	outfile << "    #####o###" << std::endl;
	outfile << "   #o#\\#|#/###" << std::endl;
	outfile << "    ###\\|/#o#" << std::endl;
	outfile << "     # }|{  #" << std::endl;
	outfile << "       }|{" << std::endl;
	outfile.close();
}
