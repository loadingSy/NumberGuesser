#pragma once

#include <string>
#include "ConsoleTypes.h"

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
    const Theme ModernDark = {
        "Modern Dark",
        Console::TextColor::White,
        Console::TextColor::Yellow,
        Console::TextColor::Red,
        Console::TextColor::Green,
        Console::TextColor::Blue,
        Console::TextColor::Red,
        Console::BgColor::Black,
        Console::TextColor::Cyan
    };

    const Theme ClassicGreen = {
        "Classic Green",
        Console::TextColor::Green,
        Console::TextColor::White,
        Console::TextColor::Red,
        Console::TextColor::Yellow,
        Console::TextColor::Cyan,
        Console::TextColor::Magenta,
        Console::BgColor::Black,
        Console::TextColor::Green
    };

    const Theme Sunset = {
        "SunSet",
        Console::TextColor::Yellow,
        Console::TextColor::White,
        Console::TextColor::Red,
        Console::TextColor::Green,
        Console::TextColor::Cyan,
        Console::TextColor::Magenta,
        Console::BgColor::Black,
        Console::TextColor::Yellow
    };

    const Theme Paper = {
        "Paper",
        Console::TextColor::Black,
        Console::TextColor::Blue,
        Console::TextColor::Red,
        Console::TextColor::Green,
        Console::TextColor::Blue,
        Console::TextColor::Red,
        Console::BgColor::White,
        Console::TextColor::Black
    };

    const Theme Neon = {
        "Neon",
        Console::TextColor::Cyan,
        Console::TextColor::Yellow,
        Console::TextColor::Red,
        Console::TextColor::Green,
        Console::TextColor::Blue,
        Console::TextColor::Magenta,
        Console::BgColor::Black,
        Console::TextColor::Magenta
    };
}
