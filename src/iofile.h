#pragma once

#include "contact.h"
#include <filesystem>
#include <map>
#include <regex>
#include <string>
#include <vector>

class fileInputOutput {
public:
    static void saveToFile(std::map<std::string, Contact> contactCollection, std::filesystem::path path);

    static std::map<std::string, Contact> readFromFile(std::filesystem::path path);
};

class serializationUtilities {
public:
    static std::string serializeContact(Contact& c);

    static Contact contactFromSerialization(std::string_view s);

    static std::vector<std::string> tokenizeString(std::string s, std::regex reg);
};
