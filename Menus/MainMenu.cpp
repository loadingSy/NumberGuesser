#include <iostream>
#include <vector>
#include "Menu.h"
#include "../HelperFunctions.h"
#include "../SaveLoad.h"
#include "ShopMenu.h"
#include "SettingsMenu.h"
#include "../GameSettings/GameSettings.h"
#include "GameLoop.h"
#include "StatsMenu.h"


std::vector<menuTab> mainMenuTabs = 
{
    {"Play", [](){GameMenu.open();}},
    {"Shop", [](){ShopMenu.open();}},
    {"Settings", [](){SettingsMenu.open();}},
    {"Check Stats", [](){StatsMenu.open();}}
};

menu MainMenu("Main Menu",mainMenuTabs,true);



