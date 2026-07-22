#pragma once

#include <iostream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include "ConsoleTypes.h"
#include "Theme.h"
#include "SaveLoad.h"

namespace Console
{
    void setTerminalColors(TextColor tColor = TextColor::None, BgColor bgColor = BgColor::None);
    void undoTerminalColor();
    void resetTerminalColor();
    std::string getStyleString(TextColor tColor = TextColor::None, BgColor bColor = BgColor::None, bool saveColor = false);
}


bool inRange(int num, int min, int max);

template<typename T>
T ask(std::string question);

int randomInRange(int min, int max);
template<typename T>
T validateInput(std::string stringToCheck);
void returnError(std::string errorMessage);


template<>
inline int validateInput<int>(const std::string stringToCheck)
{
    try
    {
        int processedInput =  stoi(stringToCheck);
        return processedInput;
    }
    catch (std::invalid_argument& reason) {
        returnError(reason.what());
        return -1;
    }
    catch (std::out_of_range& reason)
    {
        returnError(reason.what());
        return -1;
    }
}

template<>
inline bool validateInput<bool>(const std::string stringToCheck)
{
    if(!stringToCheck.empty())
    {
        char firstLetter = std::tolower(stringToCheck[0]);
        if(firstLetter == 'y' || firstLetter == '1')
        {
            return true;
        }
    }
    return false;
}

template <>
inline int ask<int>(std::string question)
{
    bool answered = false;
    std::string userInput;
    while (!answered) 
    {
        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << question << "\n" << Console::getStyleString(tempRunningSaveData.currentTheme.promptColor);
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
inline bool ask<bool>(std::string question)
{
    bool answered = false;
    std::string userInput;
    while (!answered) 
    {
        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << question << "\n" << Console::getStyleString(tempRunningSaveData.currentTheme.promptColor);
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
inline std::string ask<std::string>(std::string question)
{
    bool answered = false;
    std::string userInput;
    while (!answered) 
    {
        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << question << "\n" << Console::getStyleString(tempRunningSaveData.currentTheme.promptColor);
        std::cin >> userInput;
        std::string validatedInput = userInput;
        if(validatedInput.empty())
        {
            answered = false;
            continue;
        }
        return validatedInput;
    }
    return "";
} 
namespace Console
{
    extern std::string lastState;
    extern std::string currentState;
}

