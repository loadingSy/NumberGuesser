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
namespace Console
{
    extern std::string lastState;
    extern std::string currentState;
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
    void undoTerminalColor();
    void resetTerminalColor();
    std::string getStyleString(TextColor tColor, BgColor bColor);
}

struct Theme
{
    std::string name;
    Console::TextColor primaryColor;
    Console::TextColor boldColor;

    Console::TextColor negativeColor;
    Console::TextColor positiveColor;

    Console::TextColor lowColor;
    Console::TextColor highColor;

    Console::BgColor backgroundColor;
    Console::TextColor promptColor;
};

namespace Themes {
    // Clean, modern default (High contrast, easy to read)
    const Theme ModernDark = {
        "Modern Dark",
        Console::TextColor::White,    // primaryColor
        Console::TextColor::Yellow,   // boldColor
        Console::TextColor::Red,      // negativeColor
        Console::TextColor::Green,    // positiveColor
        Console::TextColor::Blue,     // lowColor (Cold = Too Low)
        Console::TextColor::Red,      // highColor (Hot = Too High)
        Console::BgColor::Black,      // backgroundColor
        Console::TextColor::Cyan      // promptColor
    };

    // Monochrome CRT style (Minimalist, easy on the eyes)
    const Theme ClassicGreen = {
        "Classic Green",
        Console::TextColor::Green,    // primaryColor
        Console::TextColor::White,    // boldColor
        Console::TextColor::Red,      // negativeColor
        Console::TextColor::Yellow,   // positiveColor
        Console::TextColor::Cyan,     // lowColor
        Console::TextColor::Magenta,  // highColor
        Console::BgColor::Black,      // backgroundColor
        Console::TextColor::Green     // promptColor
    };

    // Sunset Palette (Warm tones for numbers and guidance)
    const Theme Sunset = {
        "SunSet",
        Console::TextColor::Yellow,   // primaryColor
        Console::TextColor::White,    // boldColor
        Console::TextColor::Red,      // negativeColor
        Console::TextColor::Green,    // positiveColor
        Console::TextColor::Cyan,     // lowColor
        Console::TextColor::Magenta,  // highColor
        Console::BgColor::Black,      // backgroundColor
        Console::TextColor::Yellow    // promptColor
    };

    // High Contrast Light Mode (Inverted terminal)
    const Theme Paper = {
        "Paper",
        Console::TextColor::Black,    // primaryColor
        Console::TextColor::Blue,     // boldColor
        Console::TextColor::Red,      // negativeColor
        Console::TextColor::Green,    // positiveColor
        Console::TextColor::Blue,     // lowColor
        Console::TextColor::Red,      // highColor
        Console::BgColor::White,      // backgroundColor
        Console::TextColor::Black     // promptColor
    };

    // Cyberpunk Neon (Vibrant contrast)
    const Theme Neon = {
        "Neon",
        Console::TextColor::Cyan,     // primaryColor
        Console::TextColor::Yellow,   // boldColor
        Console::TextColor::Red,      // negativeColor
        Console::TextColor::Green,    // positiveColor
        Console::TextColor::Blue,     // lowColor
        Console::TextColor::Magenta,  // highColor
        Console::BgColor::Black,      // backgroundColor
        Console::TextColor::Magenta   // promptColor
    };
}
