#include <iostream>
#include "MenuLoader.h"

MenuLoader::MenuLoader()
{

}

int MenuLoader::createMenu(std::string menuID, std::string pathToMenu)
{
    MenuMap::iterator menuIter = _mMenuMap.find(menuID);
    if (menuIter != _mMenuMap.end()) {
        std::cout << "MenuID of " << menuID << " is already in use." << std::endl;
        return 1;
    }
    _mMenuMap.insert(std::pair<std::string, std::string>(menuID, pathToMenu));
    return 0;
}

int MenuLoader::displayMenu(std::string menuID)
{
    MenuMap::iterator menuIter = _mMenuMap.find(menuID);
    if (menuIter == _mMenuMap.end()) {
        std::cout << "Invalid menuID: " << menuID << std::endl;
        return 1;
    }
    std::fstream menuHandle;
    menuHandle.open(menuIter->second, std::ios::in);
    if (!menuHandle) {
        std::cout << "Couldn't open file at path: " << menuIter->second << std::endl;
        return 1;
    }
    for (std::string line; std::getline(menuHandle, line); ) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
    menuHandle.close();
    return 0;
}
