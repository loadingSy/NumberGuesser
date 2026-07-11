#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Menu.h"



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
    std::stringstream askSS;
    int tabCount = 1;
    for(auto tab : tabs)
    {
        askSS << tabCount << ". " << tab.name << "\n";
        tabCount++;
    }
    if(hasLeave)
    {
        askSS << tabCount << ". " << "Leave" << "\n";
    }
    std::string askQuestion = askSS.str();
    bool acceptedInput = false;
    int chosenTab;
    while(!acceptedInput)
    {
        chosenTab = ask<int>(askQuestion); 
        acceptedInput = inRange(chosenTab, 1, (hasLeave? tabCount : tabCount - 1));
    }
    return chosenTab;
}

bool menu::recurseTabs(const std::vector<menuTab> tabs)
{
    std::cout << "\n" << name << "\n";
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
