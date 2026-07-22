#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <random>
#include "SaveLoad.h"
#include "HelperFunctions.h"
#include "Menus/Menu.h"
#include "Menus/MainMenu.h"
#include "Menus/ShopMenu.h"
#include "Menus/GameLoop.h"
#include "Menus/ThemesMenu.h"
#include "Theme.h"

using namespace std;









int main()
{
    if (loadSaveData(fileName, tempRunningSaveData)) 
    {
        cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << "Save data file loaded Successfully!\n";
    }
    else {
        cout << Console::getStyleString(Themes::Paper.negativeColor) << "Save data file Not Found Creating new one...\n";
        if(saveTempData(fileName, tempRunningSaveData))
        {
            cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << "Finished Saving successfully\n";
        }
        else {
            cout << Console::getStyleString(Themes::Paper.positiveColor) << "Saving Failed..\n";
        }
        
    }
    
    cout << Console::getStyleString(tempRunningSaveData.currentTheme.boldColor) << "Press Enter to start: ";
    ShopMenu.initialize();
    GameMenu.initialize();
    themesMenu.initialize();

    Console::setTerminalColors(tempRunningSaveData.currentTheme.primaryColor,tempRunningSaveData.currentTheme.backgroundColor);

    cin.get();
    MainMenu.open();
    
    
}








