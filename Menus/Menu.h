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
    std::vector<menuTab> mainTabs;
    void open()
    {
        mainLoop();
    }
    menu(std::string cName, std::vector<menuTab> tabs)
    {
        mainTabs = tabs;
        name = cName;
    }
    template<typename T>
    T ask(std::string question);
    int askTabs(std::vector<menuTab> tabs);
    private:
    void mainLoop();
};

template <>
inline int menu::ask<int>(std::string question)
{
    bool answered = false;
    std::string userInput;
    while (!answered) 
    {
        std::cout << question << "\n";
        std::cin >> userInput;
        int validatedInput = validateInput<int>(userInput);
        if(validatedInput < 1 || validatedInput > 10000)
        {
            answered = false;
            continue;
        }
        answered = true;
        return validatedInput;
    }
    return -1;
}

template <>
inline bool menu::ask<bool>(std::string question)
{
    bool answered = false;
    std::string userInput;
    while (!answered) 
    {
        std::cout << question << "\n";
        std::cin >> userInput;
        bool validatedInput = validateInput<bool>(userInput);
        if(!validatedInput)
        {
            answered = false;
            continue;
        }
        return validatedInput;
    }
}

template<>
inline std::string menu::ask<std::string>(std::string question)
{
    bool answered = false;
    std::string userInput;
    while (!answered) 
    {
        std::cout << question << "\n";
        std::cin >> userInput;
        std::string validatedInput = userInput;
        if(validatedInput.empty())
        {
            answered = false;
            continue;
        }
        return validatedInput;
    }
} 

