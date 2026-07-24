#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Menu.h"
#include "../HelperFunctions.h"
#include "../SaveLoad.h"

int leaveOption = -1;
void menu::mainLoop()
{
    bool continueLoop = true;
    while (continueLoop) 
    {
        continueLoop = recurseTabs(mainTabs);
    }
}

int menu::askTabs(const std::vector<menuTab>& tabs, int tabToStart)
{
    int displayedItemsPerPage = 6;
    using namespace Console;
    Theme& currTheme = tempRunningSaveData.currentTheme;
    std::stringstream askSS;
    int tabCount = 1;
    bool otherPage = false;
    for(int i = tabToStart; i < tabs.size(); i++)
    {
        auto tab = tabs[i];
        askSS << getStyleString(currTheme.promptColor, BgColor::None, true) << tabCount << ". " << getStyleString(currTheme.boldColor, BgColor::None, true) << tab.name << "\n";
        tabCount++;
        if(tabCount == displayedItemsPerPage + 1 && (i + 1) < tabs.size())
        {
            otherPage = true;
            break;
        }
    }
    int nextPageOption;
    if(otherPage)
    {
        nextPageOption = tabCount;
        askSS << getStyleString(currTheme.promptColor, BgColor::None, true) << tabCount << ". " << getStyleString(currTheme.boldColor, BgColor::None, true) << "Next Page..." << "\n";
        tabCount++;
    }
    if(hasLeave)
    {
        leaveOption = tabCount;
        askSS << getStyleString(currTheme.promptColor, BgColor::None, true) << (tabCount == 10 ? 0 : tabCount)  << ". " << getStyleString(currTheme.boldColor, BgColor::None, true) << "Leave" << "\n";
    }
    std::string askQuestion = askSS.str();
    bool acceptedInput = false;
    int chosenTab;
    while(!acceptedInput)
    {
        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.promptColor);
        chosenTab = ask<int>(askQuestion); 
        acceptedInput = inRange(chosenTab, 0, (hasLeave? tabCount : tabCount - 1));
        
    }
    int tabsPrinted = tabCount-1;
    if(otherPage && chosenTab == nextPageOption)
    {
        return askTabs(tabs, tabToStart + displayedItemsPerPage);
    }
    return chosenTab+tabToStart-1;
}

bool menu::recurseTabs(const std::vector<menuTab>& tabs)
{
    std::cout << "\n" << Console::getStyleString(tempRunningSaveData.currentTheme.boldColor) << name << "\n";
    int chosenTab = askTabs(tabs)-1;
    if(hasLeave && chosenTab == leaveOption)
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
