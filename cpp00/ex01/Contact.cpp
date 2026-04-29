#include "Contact.hpp"

void Contact::setFirstName(const std::string &v){ firstName = v;}
void Contact::setLastName(const std::string &v){ lastName = v;}
void Contact::setNickName(const std::string &v){ nickName = v;}
void Contact::setPhoneNumber(const std::string &v){ phoneNumber = v;}
void Contact::setDarkestSecret(const std::string &v){darkestSecret = v;}

std::string Contact::getFirstName() const { return firstName;}
std::string Contact::getLastName() const {return lastName;}
std::string Contact::getNickName() const {return nickName;}
std::string Contact::getPhoneNumber() const {return phoneNumber;}
std::string Contact::getDarkestSecret() const {return darkestSecret;}
