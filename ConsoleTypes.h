#pragma once

namespace Console
{
    enum class TextColor {
        None    = 0,
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
}
