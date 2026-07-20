#pragma once

#include <iostream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>


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
inline bool ask<bool>(std::string question)
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
inline std::string ask<std::string>(std::string question)
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
    return "";
} 

enum class TextColor {
    None    = 0, // Used when you don't want to change this layer
    Default = 39,
    Black   = 30, Red     = 31, Green   = 32, Yellow = 33,
    Blue    = 34, Magenta = 35, Cyan    = 36, White  = 37
};

enum class BgColor {
    None    = 0,
    Default = 49,
    Black   = 40, Red     = 41, Green   = 42, Yellow = 43,
    Blue    = 44, Magenta = 45, Cyan    = 46, White  = 47
};

void setTerminalColors(TextColor tColor = TextColor::None, BgColor bgColor = BgColor::None);