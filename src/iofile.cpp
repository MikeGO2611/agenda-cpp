#include "iofile.h"
#include "contact.h"
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

void fileInputOutput::saveToFile(std::map<std::string, Contact> contactCollection, std::filesystem::path path)
{
    std::ofstream fileout(path, std::ios::out);

    for (auto it = contactCollection.begin(); it != contactCollection.end(); ++it) {
        if (it != contactCollection.begin()) {
            fileout << "---\n";
        }
        fileout << serializationUtilities::serializeContact(it->second) << "\n";
    }

    fileout.close();
}

std::map<std::string, Contact> fileInputOutput::readFromFile(std::filesystem::path path)
{
    std::map<std::string, Contact> contactCollection;

    std::ifstream filein(path, std::ios::in);

    std::string s;

    std::string buffer;

    while (std::getline(filein, buffer)) {
        s.append(buffer + "\n");
    }

    std::vector<std::string> serializedContactCollection { serializationUtilities::tokenizeString(s, std::regex { "---" }) };

    for (std::string serializedContact : serializedContactCollection) {
        Contact c = serializationUtilities::contactFromSerialization(serializedContact);
        contactCollection.emplace(c.getName(), c);
    }

    return contactCollection;
}
std::string serializationUtilities::serializeContact(Contact& c)
{
    return "Name: " + static_cast<std::string>(c.getName()) + "\n"
        + "Address: " + static_cast<std::string>(c.getAddress()) + "\n"
        + "PhoneNumber: " + static_cast<std::string>(c.getPhoneNumber());
}

Contact serializationUtilities::contactFromSerialization(std::string_view s)
{

    std::vector<std::string> tokens { serializationUtilities::tokenizeString(std::string { s }, std::regex { "\\s|\\n" }) };

    return { tokens[1], tokens[3], tokens[5] };
}

std::vector<std::string> serializationUtilities::tokenizeString(std::string s, std::regex reg)
{
    std::sregex_token_iterator it { s.begin(), s.end(), reg, -1 };
    std::sregex_token_iterator end;
    std::vector<std::string> tokens;

    while (it != end) {
        if (it->length()) {
            tokens.push_back(*it);
        }
        ++it;
    }

    return tokens;
}
