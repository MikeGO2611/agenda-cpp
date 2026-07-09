#include "menu.h"
#include "contact.h"
#include "contactModel.h"
#include <climits>
#include <ios>
#include <iostream>
#include <limits>
#include <string>

Menu::Menu(ContactModel* contactModel)
    : m_contactModel { contactModel }
{
}

void Menu::start()
{
    showMenu();
}

void Menu::showMenu()
{
    bool exit { false };

    while (!exit) {
        std::cout << "=== Agenda ===" << "\n\n"
                  << "1) Buscar Contacto" << "\n"
                  << "2) Añadir Contacto" << "\n"
                  << "3) Modificar Contacto" << "\n"
                  << "4) Eliminar Contacto" << "\n"
                  << "5) Mostrar toda la Agenda" << "\n"
                  << "6) Salir" << "\n\n";

        int selection;

        std::cin >> selection;

        std::cout << "\n";

        switch (selection) {
        case 1:
            searchContactMenu();
            break;
        case 2:
            addContactMenu();
            break;
        case 3:
            modifyContactMenu();
            break;
        case 4:
            deleteContactMenu();
            break;
        case 5:
            showAllAgenda();
            break;
        case 6:
            exit = true;
            break;
        default:
            std::cout << "Opción no válida, selecciona un número del menú.\n";
            break;
        }

        std::cout << "\n";
    }
}

void Menu::searchContactMenu()
{
    std::string name;

    clearInput();

    std::cout << "Introduce el nombre del contacto para buscar: ";
    std::getline(std::cin, name);

    Contact* contact = m_contactModel->findContact(name);

    if (contact != nullptr) {
        std::cout << "\n"
                  << *contact;
    } else {
        std::cout << "Contacto no encontrado.\n";
    }
}

void Menu::addContactMenu()
{

    clearInput();

    std::cout << "Introduce la información del contacto a añadir.\n";
    Contact contactToAdd { askForContactInfo() };

    if (m_contactModel->doesContactExist(contactToAdd)) {
        std::cout << "El contacto ya existe.\n";
        return;
    }

    m_contactModel->addContact(contactToAdd);
}

void Menu::modifyContactMenu()
{
    std::string searchName;

    clearInput();

    std::cout << "Introduce el nombre del contacto a modificar: ";
    std::getline(std::cin, searchName);

    if (!m_contactModel->doesContactExist(searchName)) {
        std::cout << "El contacto no existe.";
        return;
    }

    std::cout << "Introduce la información nueva del contacto.\n";
    Contact updatedContact { askForContactInfo() };

    if (updatedContact.getName() == searchName) {
        m_contactModel->modifyContact(searchName, static_cast<std::string>(updatedContact.getAddress()), static_cast<std::string>(updatedContact.getPhoneNumber()));
    } else {
        m_contactModel->removeContact(searchName);
        m_contactModel->addContact(updatedContact);
    }


    std::cout << "Contacto actualizado correctamente.\n";
}

void Menu::deleteContactMenu()
{
    std::string searchName;

    clearInput();

    std::cout << "Introduce el nombre del contacto a modificar: ";
    std::getline(std::cin, searchName);

    if (!m_contactModel->doesContactExist(searchName)) {
        std::cout << "El contacto no existe.";
        return;
    }

    m_contactModel->removeContact(searchName);

    std::cout << "Contacto con nombre " << searchName << " eliminado correctamente.\n";
}

void Menu::showAllAgenda()
{
    auto contactCollection = m_contactModel->getContactCollection();

    for (auto it { contactCollection.begin() }; it != contactCollection.end(); ++it) {
        std::cout << it->second << "\n";
    }
}

void Menu::clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Contact Menu::askForContactInfo()
{
    std::string name;
    std::string address;
    std::string phoneNumber;

    std::cout << "Nombre: ";
    std::getline(std::cin, name);
    std::cout << "Dirección: ";
    std::getline(std::cin, address);
    std::cout << "Número de Teléfono: ";
    std::getline(std::cin, phoneNumber);

    std::cout << "\n";

    return { name, address, phoneNumber };
}
