#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : count(0), nextIndex(0){}

void PhoneBook::addContact(const Contact &c)
{
    contacts[nextIndex] = c;
    nextIndex = (nextIndex + 1) % MAX_CONTACTS;
    if (count < MAX_CONTACTS)
        count++;
}

static std::string formatColumn(const std::string &s) {
    if (s.length() > 10){
        std::string truncated = s.substr(0, 9);
        truncated += '.';
        return truncated;
    }
    return s;
}

void PhoneBook::searchContact() const {
    if(count == 0){
        std::cout << "Phonebook is empty." << std::endl;
        return;
    }

    std::cout << std::setw(10) << std::right << "index" << "|"
              << std::setw(10) << std::right << "First name" << "|"
              << std::setw(10) << std::right << "Last name" << "|"
              << std::setw(10) << std::right << "Nickname" << std::endl;

    for (int i = 0; i < count; ++i){
        std::cout << std::setw(10) << std::right << i << "|"
                  << std::setw(10) << std::right << formatColumn(contacts[i].getFirstName()) << "|"
                  << std::setw(10) << std::right << formatColumn(contacts[i].getLastName()) << "|"
                  << std::setw(10) << std::right << formatColumn(contacts[i].getNickName()) << std::endl;
    }

    std::cout << "Enter index: ";
    std::string input;
    if(!std::getline(std::cin, input)){
        std::cout << std::endl;
        return;
    }

    int idx = std::atoi(input.c_str());
    if (idx < 0 || idx >= count){
        std::cout << "Invalid index." << std::endl;
        return;
    }

    std::cout << "First name      : " << contacts[idx].getFirstName()  << std::endl;
    std::cout << "Last name       : " << contacts[idx].getLastName()  << std::endl;
    std::cout << "Nick name       : " << contacts[idx].getNickName()  << std::endl;
    std::cout << "Phone number    : " << contacts[idx].getPhoneNumber()  << std::endl;
    std::cout << "Darkest secret  : " << contacts[idx].getDarkestSecret()  << std::endl;

}