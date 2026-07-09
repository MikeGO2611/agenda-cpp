#include "contactModel.h"
#include "contact.h"
#include "iofile.h"
#include <string>
#include <utility>

ContactModel::ContactModel(std::filesystem::path path)
    : m_path { path }
{
}

ContactModel::ContactModel(std::map<std::string, Contact> contactCollection, std::filesystem::path path)
    : m_contactCollection { std::move(contactCollection) }
    , m_path { path }
{
}

void ContactModel::operator()(std::map<std::string, Contact> contactCollection)
{
    m_contactCollection = std::move(contactCollection);
}

Contact* ContactModel::findContact(const std::string& name)
{
    auto it = m_contactCollection.find(name);
    if (it != m_contactCollection.end()) {
        return &(it->second);
    } else {
        return nullptr;
    }
}

Contact* ContactModel::findContact(const Contact& contact)
{
    return findContact(std::string(contact.getName()));
}

bool ContactModel::doesContactExist(const Contact& contact)
{
    return findContact(contact) != nullptr;
}

bool ContactModel::doesContactExist(const std::string& name)
{
    return findContact(name) != nullptr;
}

void ContactModel::addContact(const Contact contact)
{
    m_contactCollection.emplace(std::pair<std::string, Contact> { contact.getName(), contact });
    updateFile();
}


void ContactModel::removeContact(const std::string& name)
{
    m_contactCollection.erase(name);
    updateFile();
}

void ContactModel::modifyContact(const std::string& name, const std::string address, const std::string phoneNumber)
{
    Contact* contact = &m_contactCollection.at(name);
    contact->setAddress(address);
    contact->setPhoneNumber(phoneNumber);
    updateFile();
}

const std::map<std::string, Contact>& ContactModel::getContactCollection() const
{
    return m_contactCollection;
}

void ContactModel::updateFile()
{
    fileInputOutput::saveToFile(m_contactCollection, m_path);
}
