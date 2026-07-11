#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Menu.h"



void menu::mainLoop()
{
    while(true)
    {
    std::cout << "\n" << name << "\n";
    int chosenTab = askTabs(mainTabs)-1;
    if(mainTabs[chosenTab].childrens.index() == 1)
    {
        askTabs(std::get<1>(mainTabs[chosenTab].childrens));
    }
    else {
        std::function<void()> func = std::get<0>(mainTabs[chosenTab].childrens);
        func();
    }
    
    
    }
}

int menu::askTabs(std::vector<menuTab> tabs)
{
    std::stringstream askSS;
    int tabCount = 1;
    for(auto tab : tabs)
    {
        askSS << tabCount << ". " << tab.name << "\n";
        tabCount++;
    }
    std::string askQuestion = askSS.str();
    bool acceptedInput = false;
    int chosenTab;
    while(!acceptedInput)
    {
        chosenTab = ask<int>(askQuestion); 
        acceptedInput = inRange(chosenTab, 1, tabCount - 1);
    }
    return chosenTab;
}


