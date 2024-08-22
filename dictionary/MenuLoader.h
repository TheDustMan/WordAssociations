#ifndef _MENU_LOADER_H_
#define _MENU_LOADER_H_

#include <fstream>
#include <ios>
#include <map>
#include <string>

class MenuLoader {
public:
  MenuLoader();
  int createMenu(std::string menuID, std::string pathToMenu);
  int displayMenu(std::string menuID);

private:
  typedef std::map<std::string /*=menuID*/, std::string /*=pathToMenu*/>
      MenuMap;
  MenuMap _mMenuMap;
};

#endif /* _MENU_LOADER_H_ */
