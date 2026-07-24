#include <iostream>
#include <sstream>
#include <vector>
#include "../SaveLoad.h"
#include "Menu.h"

std::vector<menuTab> themesTabs = {};

void themesInitialize();

menu themesMenu("Themes",themesTabs,true,themesInitialize);

void previewTheme(const Theme& currTheme)
{
    using namespace Console;
    std::stringstream themeSS;

    themeSS << Console::getStyleString(currTheme.boldColor, currTheme.backgroundColor) 
            << "=== NUMBER GUESSER ===" 
            << "\033[0m\n\n";

    themeSS << Console::getStyleString(currTheme.primaryColor, currTheme.backgroundColor) 
            << "Lorem ipsum dolor sit amet, consectetur adipiscing elit." 
            << "\033[0m\n\n";

    themeSS << Console::getStyleString(currTheme.promptColor, currTheme.backgroundColor) 
            << "Enter your guess > " 
            << "\033[0m\n";

    themeSS << Console::getStyleString(currTheme.lowColor, currTheme.backgroundColor) 
            << "Too Low! Lorem ipsum dolor sit amet." 
            << "\033[0m\n";

    themeSS << Console::getStyleString(currTheme.highColor, currTheme.backgroundColor) 
            << "Too High! Lorem ipsum dolor sit amet." 
            << "\033[0m\n";

    themeSS << Console::getStyleString(currTheme.positiveColor, currTheme.backgroundColor) 
            << "Correct! Lorem ipsum dolor sit amet." 
            << "\033[0m\n";

    themeSS << Console::getStyleString(currTheme.negativeColor, currTheme.backgroundColor) 
            << "Error! Lorem ipsum dolor sit amet." 
            << "\033[0m\n";
    std::cout << themeSS.str();
    std::cout << "Press Enter to return...";
    std::cin.ignore();
    std::cin.get();
}

void applyTheme(const Theme& currTheme)
{
    tempRunningSaveData.currentTheme = currTheme;
    saveTempData(fileName, tempRunningSaveData);
    std::cout << Console::getStyleString(Console::TextColor::None,currTheme.backgroundColor);
}

void themesInitialize()
{
    themesTabs.clear();

    for (size_t i = 0; i < tempRunningSaveData.ThemesOwned.size(); i++)
    {
        auto currTheme = tempRunningSaveData.ThemesOwned[i];
        themesTabs.push_back(
            menuTab(
                currTheme.name,
                std::vector<menuTab>{
                    menuTab("Preview", [currTheme](){ previewTheme(currTheme); }),
                    menuTab("Apply",   [currTheme](){ applyTheme(currTheme);   })
                }
            )
        );
    }
    saveTempData(fileName, tempRunningSaveData);
}

