#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
private:
	std::string firstName;
	std::string lastName;
	std::string nickName;
	std::string phoneNumber;
	std::string darkestSecret;

public:
	void setFirstName(const std::string &v);
    void setLastName(const std::string &v);
    void setNickName(const std::string &v);
    void setPhoneNumber(const std::string &v);
    void setDarkestSecret(const std::string &v);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getNickName() const;
    std::string getPhoneNumber() const;
    std::string getDarkestSecret() const;

};
#endif