#pragma once

#include "contact.h"
#include "contactModel.h"
class Menu {
private:
    ContactModel* m_contactModel;

    void showMenu();
    void searchContactMenu();
    void addContactMenu();
    void modifyContactMenu();
    void deleteContactMenu();
    void showAllAgenda();
    void clearInput();
    Contact askForContactInfo();

public:
    Menu(ContactModel* contactModel);
    void start();
};
