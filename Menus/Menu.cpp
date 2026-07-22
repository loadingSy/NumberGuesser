#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Menu.h"
#include "../HelperFunctions.h"
#include "../SaveLoad.h"


void menu::mainLoop()
{
    bool continueLoop = true;
    while (continueLoop) 
    {
        continueLoop = recurseTabs(mainTabs);
    }
}

int menu::askTabs(const std::vector<menuTab>& tabs)
{
    using namespace Console;
    Theme& currTheme = tempRunningSaveData.currentTheme;
    std::stringstream askSS;
    int tabCount = 1;
    for(auto tab : tabs)
    {
        askSS << getStyleString(currTheme.promptColor, BgColor::None, true) << tabCount << ". " << getStyleString(currTheme.boldColor, BgColor::None, true) << tab.name << "\n";
        tabCount++;
    }
    if(hasLeave)
    {
        askSS << getStyleString(currTheme.promptColor, BgColor::None, true) << tabCount << ". " << getStyleString(currTheme.boldColor, BgColor::None, true) << "Leave" << "\n";
    }
    std::string askQuestion = askSS.str();
    bool acceptedInput = false;
    int chosenTab;
    while(!acceptedInput)
    {
        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.promptColor);
        chosenTab = ask<int>(askQuestion); 
        acceptedInput = inRange(chosenTab, 1, (hasLeave? tabCount : tabCount - 1));
    }
    return chosenTab;
}

bool menu::recurseTabs(const std::vector<menuTab>& tabs)
{
    std::cout << "\n" << Console::getStyleString(tempRunningSaveData.currentTheme.boldColor) << name << "\n";
    int chosenTab = askTabs(tabs)-1;
    if(hasLeave && chosenTab == tabs.size())
    {
        return false;
    }
    if(tabs[chosenTab].childrens.index() == 1)
    {
        recurseTabs(std::get<1>(tabs[chosenTab].childrens));
    }
    else {
        std::function<void()> func = std::get<0>(tabs[chosenTab].childrens);
        func();
    }
    return true;
}
