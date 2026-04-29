#include "Contact.hpp"
#include "PhoneBook.hpp"

static bool promptField(const std::string &label, std::string &out){
	while(true){
		std::cout <<label <<": ";
		if(!std::getline(std::cin, out))
			return false;
		if(!out.empty())
			return true;
		std::cout << "Field cannot be empty. Try again." <<std::endl;
	}
}

static void doadd(PhoneBook &pb)
{
	Contact c;
	std::string s;

	if(!promptField("First name", s)) return;
	c.setFirstName(s);
	if(!promptField("Last name", s)) return;
	c.setLastName(s);
	if(!promptField("Nick name", s)) return;
	c.setNickName(s);
	if(!promptField("Phone number", s)) return;
	c.setPhoneNumber(s);
	if(!promptField("Darkest secret", s)) return;
	c.setDarkestSecret(s);

	pb.addContact(c);

}
int main() {
	PhoneBook pb;
	std::string command;

	while(true)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, command))
			break;

		if(command == "ADD")
			doadd(pb);
		else if(command == "SEARCH")
			pb.searchContact();
		else if(command == "EXIT")
			break;
	}
	return 0;
}
