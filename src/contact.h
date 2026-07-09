#pragma once

#include <ostream>
#include <string>
#include <string_view>

class Contact {
private:
    std::string m_name;
    std::string m_address;
    std::string m_phoneNumber;
public:
    Contact(const std::string_view name, const std::string_view address, const std::string_view phoneNumber);

    std::string_view getName() const;
    std::string_view getAddress() const;
    std::string_view getPhoneNumber() const;

    void setAddress(const std::string address);
    void setPhoneNumber(const std::string address);

    friend bool operator==(const Contact& c1, const Contact& c2);
    friend std::weak_ordering operator<=>(const Contact& c1, const Contact& c2);
    friend std::ostream& operator<<(std::ostream& out, const Contact& contact);
};
