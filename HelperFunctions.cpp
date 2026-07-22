#include "HelperFunctions.h"
#include <_mingw_stat64.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <random>
#include "SaveLoad.h"
#include "Theme.h"


void returnError(std::string errorMessage);

int randomInRange(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max);
    return dist6(rng);
}

bool inRange(int num, int min, int max)
{
    return num >= min && num <= max;
}

void returnError(std::string errorMessage)
{
    std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.negativeColor) << "Error happened: " << errorMessage << "\n";
}

namespace Console {
    std::string lastState = "\033[0m";
    std::string currentState = "\033[0m";
    std::string getStyleString(TextColor tColor, BgColor bColor, bool saveColor)
    {
        if (tColor == TextColor::None && bColor == BgColor::None)
        {
            return "";
        }

        std::stringstream ss;
        ss << "\033[";

        if (tColor != TextColor::None)
        {
            ss << static_cast<int>(tColor);
        }

        if (bColor != BgColor::None)
        {
            if (tColor != TextColor::None)
            {
                ss << ";";
            }
            ss << static_cast<int>(bColor);
        }

        ss << "m";
        if(saveColor) currentState = ss.str();
        return ss.str();
    }
    void setTerminalColors(TextColor tColor, BgColor bColor)
    {
        

        lastState = currentState;

        std::stringstream ss;
        ss<<"\033[";
        
        if(tColor != TextColor::None)
        {
            ss << static_cast<int>(tColor);
        }

        if(bColor != BgColor::None)
        {
            if(tColor != TextColor::None)
            {
                ss << ";";
            }
            ss << static_cast<int>(bColor);
        }
        ss << "m";
        currentState = ss.str();
        std::cout << currentState;
    }

    void undoTerminalColor()
    {
        std::string lastLastState = lastState;
        std::cout << lastState;
        lastState = currentState;
        currentState = lastLastState;
    }
    void resetTerminalColor()
    {
        std::stringstream ss;
        ss << "\033[0m";
        std::cout << ss.str();
        currentState = ss.str();
    }
}
