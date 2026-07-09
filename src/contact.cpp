#include "contact.h"

#include <compare>
#include <string>

Contact::Contact(const std::string_view name, const std::string_view address, const std::string_view phoneNumber)
    : m_name { name }
    , m_address { address }
    , m_phoneNumber { phoneNumber }
{
}

std::string_view Contact::getName() const
{
    return m_name;
}

std::string_view Contact::getAddress() const
{
    return m_address;
}

std::string_view Contact::getPhoneNumber() const
{
    return m_phoneNumber;
}

void Contact::setAddress(const std::string address)
{
    m_address = address;
}
void Contact::setPhoneNumber(const std::string phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

bool operator==(const Contact& c1, const Contact& c2)
{
    return c1.m_name == c2.m_name;
}

std::weak_ordering operator<=>(const Contact& c1, const Contact& c2)
{
    if (c1.m_name == c2.m_name)
        return std::weak_ordering::equivalent;
    else
        return c1.m_name <=> c2.m_name;
}

std::ostream& operator<<(std::ostream& out, const Contact& contact)
{
    out << "Nombre: " << contact.m_name << "\n"
        << "Dirección: " << contact.m_address << "\n"
        << "Teléfono: " << contact.m_phoneNumber << "\n";

    return out;
}
