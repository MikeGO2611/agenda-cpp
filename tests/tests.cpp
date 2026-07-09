#include "tests.h"
#include "../src/contact.h"
#include "../src/iofile.h"
#include <cassert>
#include <map>
#include <string>
#include <utility>

void test()
{
    entryTest();
    collectionTest();
    serializationTest();
    serializationConstructionTest();
    saveToFileTest();
    readFromFileTest();
}

void entryTest()
{
    Contact e { "Mike", "Galicia", "+34 987654321" };

    assert(e.getName() == "Mike");
    assert(e.getAddress() == "Galicia");
    assert(e.getPhoneNumber() == "+34 987654321");
}

void collectionTest()
{
    std::map<std::string, Contact> contactCollection;

    contactCollection.emplace(std::make_pair<std::string, Contact>("Javi", { "Javi", "Madrid", "123456789" }));
    contactCollection.emplace(std::make_pair<std::string, Contact>("Mike", { "Mike", "Galicia", "987654321" }));
    contactCollection.emplace(std::make_pair<std::string, Contact>("Andrea", { "Andrea", "Valencia", "648123579" }));
    contactCollection.emplace(std::make_pair<std::string, Contact>("Beatriz", { "Beatriz", "Barcelona", "675837593" }));

    Contact foundContact = contactCollection.find("Mike")->second;
    assert(foundContact.getName() == "Mike");
}

void serializationTest()
{
    Contact c { "Mike", "Galicia", "987654321" };
    std::string s = serializationUtilities::serializeContact(c);
    assert(s == "Name: Mike\nAddress: Galicia\nPhoneNumber: 987654321");
}

void serializationConstructionTest()
{
    std::string s = "Name: Mike\nAddress: Galicia\nPhoneNumber: 987654321\n";

    Contact c = serializationUtilities::contactFromSerialization(s);

    assert(c.getName() == "Mike" && c.getAddress() == "Galicia" && c.getPhoneNumber() == "987654321");
}

void saveToFileTest()
{
    std::map<std::string, Contact> contactCollection;

    contactCollection.emplace(std::make_pair<std::string, Contact>("Javi", { "Javi", "Madrid", "123456789" }));
    contactCollection.emplace(std::make_pair<std::string, Contact>("Mike", { "Mike", "Galicia", "987654321" }));
    contactCollection.emplace(std::make_pair<std::string, Contact>("Andrea", { "Andrea", "Valencia", "648123579" }));
    contactCollection.emplace(std::make_pair<std::string, Contact>("Beatriz", { "Beatriz", "Barcelona", "675837593" }));

    fileInputOutput::saveToFile(contactCollection, "./test.txt");
}

void readFromFileTest()
{
    std::map<std::string, Contact> contactCollection { fileInputOutput::readFromFile("./test.txt")};

    Contact c = contactCollection.find("Mike")->second;
    assert(c.getName() == "Mike" && c.getAddress() == "Galicia" && c.getPhoneNumber() == "987654321");
}
