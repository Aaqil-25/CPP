#ifndef REPLACER_HPP
#define REPLACER_HPP

#include <string>

class Replacer {
public:
    static bool replace(std::string filename, std::string s1, std::string s2);

private:
    Replacer(void);
    Replacer(const Replacer& other);
    Replacer& operator=(const Replacer& other);
    ~Replacer(void);

    static bool readFile(std::string filename, std::string& content);
    static std::string replaceAll(std::string content, std::string s1, std::string s2);
    static bool writeFile(std::string filename, std::string content);
};

#endif
