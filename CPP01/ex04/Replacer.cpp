#include "Replacer.hpp"
#include <fstream>
#include <iostream>

Replacer::Replacer(void) {
}

Replacer::Replacer(const Replacer& other) {
    (void)other;
}

Replacer& Replacer::operator=(const Replacer& other) {
    (void)other;
    return *this;
}

Replacer::~Replacer(void) {
}

bool Replacer::readFile(std::string filename, std::string& content) {
    std::ifstream input(filename.c_str());

    if (!input.is_open()) {
        std::cerr << "Error: could not open file '" << filename << "'." << std::endl;
        return false;
    }

    content = std::string((std::istreambuf_iterator<char>(input)),
                          std::istreambuf_iterator<char>());
    input.close();
    return true;
}

std::string Replacer::replaceAll(std::string content, std::string s1, std::string s2) {
    std::string result;
    size_t pos = 0;
    size_t found;

    while ((found = content.find(s1, pos)) != std::string::npos) {
        result.append(content, pos, found - pos);
        result.append(s2);
        pos = found + s1.length();
    }
    result.append(content, pos, content.size() - pos);
    return result;
}

bool Replacer::writeFile(std::string filename, std::string content) {
    std::ofstream output(filename.c_str());

    if (!output.is_open()) {
        std::cerr << "Error: could not create file '" << filename << "'." << std::endl;
        return false;
    }

    output << content;
    if (!output.good()) {
        std::cerr << "Error: could not write to file '" << filename << "'." << std::endl;
        output.close();
        return false;
    }

    output.close();
    return true;
}

bool Replacer::replace(std::string filename, std::string s1, std::string s2) {
    if (s1.empty()) {
        std::cerr << "Error: search string s1 cannot be empty." << std::endl;
        return false;
    }

    std::string content;

    if (!readFile(filename, content))
        return false;

    std::string replaced = replaceAll(content, s1, s2);
    std::string outputName = filename + ".replace";

    return writeFile(outputName, replaced);
}
