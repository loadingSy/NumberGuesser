#pragma once

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>


bool inRange(int num, int min, int max);


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
