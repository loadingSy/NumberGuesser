#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <random>
#include "Menus/ShopMenu.h"
#include "SaveLoad.h"
#include "HelperFunctions.h"
#include "Menus/Menu.h"
#include "Menus/MainMenu.h"


using namespace std;









int main()
{
    if (loadSaveData(fileName, tempRunningSaveData)) 
    {
        cout << "Save data file loaded Successfully!\n";
    }
    else {
        cout << "Save data file Not Found Creating new one...\n";
        if(saveTempData(fileName, tempRunningSaveData))
        {
            cout << "Finished Saving successfully\n";
        }
        else {
            cout << "Saving Failed..\n";
        }
        
    }
    cout << "Press Enter to start: ";
    ShopMenu.initialize();
    cin.get();
    MainMenu.open();
    
}








