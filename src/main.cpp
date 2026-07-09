#include "../tests/tests.h"
#include "contactModel.h"
#include "iofile.h"
#include "menu.h"
#include <filesystem>

int main()
{
    // test();

    std::filesystem::path path { "./agenda.txt" };

    ContactModel contactModel(path);
    Menu menu{&contactModel};

    if (std::filesystem::exists(path)) {
        contactModel(fileInputOutput::readFromFile(path));
    }

    menu.start();

}
