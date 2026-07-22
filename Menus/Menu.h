#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <variant>
#include <vector>
#include "../HelperFunctions.h"


class menuTab
{
    public:
    std::variant<std::function<void()>, std::vector<menuTab>> childrens;
    std::string name;

    menuTab(std::string tabName, std::variant<std::function<void()>, std::vector<menuTab>> actionOrChildren)
        : name(tabName), childrens(actionOrChildren) {}
};


class menu
{
    public:
    std::string name;
    bool hasLeave = true;
    std::vector<menuTab>& mainTabs;
    std::function<void()> initialize = [](){};
    void open()
    {
        mainLoop();
    }
    menu(std::string cName, std::vector<menuTab>& tabs, bool cHasLeave = true, std::function<void()> cInitialize = [](){})
    : name(cName), hasLeave(cHasLeave), mainTabs(tabs), initialize(cInitialize){}
    int askTabs(const std::vector<menuTab>& tabs);
    bool recurseTabs(const std::vector<menuTab>& tabs);
    private:
    void mainLoop();
};



