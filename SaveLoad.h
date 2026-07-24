#pragma once

#include <string>
#include <vector>
#include "GameSettings/SharedTypes.h"
#include "Theme.h"
#include "include/json.hpp"

using json = nlohmann::json;

extern std::string fileName;


struct saveData
{
    int gameLoopsPlayed = 0;
    int failedGuessAttempts = 0;
    int successfullGuessAttempts = 0;
    int timesWon = 0;
    int timesLost = 0;
    int dumbInputs = 0;
    float points = 0;
    float pointsGainMultiplier = 1;
    float pointsDiscountMultiplier = 1;
    int chosenAttempts = 10;
    int guessRange = 30;
    int maxAttempts = 10;
    DifficultyEnum difficulty = custom;
    std::vector<Theme> ThemesOwned = {Themes::ClassicGreen,Themes::ModernDark,Themes::Sunset, Themes::Neon, Themes::Paper};
    Theme currentTheme = Themes::ModernDark;
    
};

extern saveData tempRunningSaveData;

bool loadSaveData(const std::string& fileName, saveData& data);

bool saveTempData(const std::string& fileName, const saveData& data);


namespace Save 
{
    template <typename T>
    json dataToJson(const T& object);
    template <typename T>
    void jsonToData(const json& object, T& output);
}