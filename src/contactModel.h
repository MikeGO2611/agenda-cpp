#pragma once

#include "contact.h"
#include <filesystem>
#include <map>
#include <string>
#include <string_view>

class ContactModel
{
    private:
        std::map<std::string, Contact> m_contactCollection;
        std::filesystem::path m_path;
        void updateFile();
    public:
        ContactModel(std::filesystem::path path);
        ContactModel(std::map<std::string, Contact> contactCollection, std::filesystem::path path);
        void operator()(std::map<std::string, Contact> contactCollection);
        Contact* findContact(const std::string& name);
        Contact* findContact(const Contact& contact);
        bool doesContactExist(const Contact& contact);
        bool doesContactExist(const std::string& name);
        void addContact(const Contact contact);
        void removeContact(const std::string& name);
        void modifyContact(const std::string& name, const std::string address, const std::string phoneNumber);
        const std::map<std::string, Contact>& getContactCollection() const;
};
