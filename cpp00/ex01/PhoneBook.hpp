#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

class PhoneBook{
private:
    static const int MAX_CONTACTS = 8;

    Contact contacts[MAX_CONTACTS];
    int     count;
    int     nextIndex;

public:
    PhoneBook();

    void addContact(const Contact &c);
    void searchContact() const;

};

#endif