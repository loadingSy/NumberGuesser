#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "GameSettings/SharedTypes.h"
#include "Theme.h"
#include "ConsoleTypes.h"
#include "include/json.hpp"

using json = nlohmann::json;

extern std::string saveFileName;

struct saveData
{
    int gameLoopsPlayed = 0;
    int failedGuessAttempts = 0;
    int successfullGuessAttempts = 0;
    int timesWon = 0;
    int timesLost = 0;
    int dumbInputs = 0;
    float points = 0.0f;
    float pointsGainMultiplier = 1.0f;
    float pointsDiscountMultiplier = 1.0f;
    int chosenAttempts = 10;
    int guessRange = 30;
    int maxAttempts = 10;
    DifficultyEnum difficulty = custom;
    std::vector<Theme> ThemesOwned = {Themes::ClassicGreen, Themes::ModernDark, Themes::Sunset, Themes::Neon, Themes::Paper};
    Theme currentTheme = Themes::ModernDark;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Theme, 
    name, primaryColor, boldColor, negativeColor, 
    positiveColor, lowColor, highColor, backgroundColor, promptColor
)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(saveData, 
    gameLoopsPlayed, failedGuessAttempts, successfullGuessAttempts, 
    timesWon, timesLost, dumbInputs, points, pointsGainMultiplier, 
    pointsDiscountMultiplier, chosenAttempts, guessRange, maxAttempts, 
    difficulty, ThemesOwned, currentTheme
)

NLOHMANN_JSON_SERIALIZE_ENUM(DifficultyEnum, {
    {DifficultyEnum::easy, 0},
    {DifficultyEnum::medium, 1},
    {DifficultyEnum::hard, 2}
})

NLOHMANN_JSON_SERIALIZE_ENUM(Console::TextColor, {
    {Console::TextColor::None, 0},
    {Console::TextColor::Default, 39},
    {Console::TextColor::Black, 30},
    {Console::TextColor::Red, 31},
    {Console::TextColor::Green, 32},
    {Console::TextColor::Yellow, 33},
    {Console::TextColor::Blue, 34},
    {Console::TextColor::Magenta, 35},
    {Console::TextColor::Cyan, 36},
    {Console::TextColor::White, 37}
})

NLOHMANN_JSON_SERIALIZE_ENUM(Console::BgColor, {
    {Console::BgColor::None, 0},
    {Console::BgColor::Default, 49},
    {Console::BgColor::Black, 40},
    {Console::BgColor::Red, 41},
    {Console::BgColor::Green, 42},
    {Console::BgColor::Yellow, 43},
    {Console::BgColor::Blue, 44},
    {Console::BgColor::Magenta, 45},
    {Console::BgColor::Cyan, 46},
    {Console::BgColor::White, 47}
})

extern saveData tempRunningSaveData;

template <typename T>
bool loadFromFile(const std::string& filePath, T& output)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return false;
    }

    try
    {
        json j;
        file >> j;
        output = j.get<T>();
        return true;
    }
    catch (const json::exception& e)
    {
        std::cerr << "JSON Load Error (" << filePath << "): " << e.what() << "\n";
        return false;
    }
}

template <typename T>
bool saveToFile(const std::string& filePath, const T& input)
{
    std::ofstream file(filePath);
    if (!file.is_open())
    {
        return false;
    }

    try
    {
        json j = input;
        file << j.dump(4);
        return true;
    }
    catch (const json::exception& e)
    {
        std::cerr << "JSON Save Error (" << filePath << "): " << e.what() << "\n";
        return false;
    }
}

bool loadSaveData(const std::string& saveFileName, saveData& data);
bool saveTempData(const std::string& saveFileName, const saveData& data);