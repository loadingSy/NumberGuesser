#include "GameSettings/SharedTypes.h"
#include "include/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "SaveLoad.h"

using json = nlohmann::json;

std::string fileName = "saveFile.txt";
saveData tempRunningSaveData;

namespace Save 
{

    template <typename T>
    json dataToJson(const T& object)
    {
        return object;
    }

    template<>
    json dataToJson<Console::TextColor>(const Console::TextColor& object)
    {
        return static_cast<int>(object);
    }

    template<>
    json dataToJson<Console::BgColor>(const Console::BgColor& object)
    {
        return static_cast<int>(object);
    }

    template<>
    json dataToJson<Theme>(const Theme& object)
    {
        return json
        {
            {"name", object.name},
            {"primaryColor", dataToJson(object.primaryColor)},
            {"boldColor", dataToJson(object.boldColor)},
            {"negativeColor", dataToJson(object.negativeColor)},
            {"positiveColor", dataToJson(object.positiveColor)},
            {"lowColor", dataToJson(object.lowColor)},
            {"highColor", dataToJson(object.highColor)},
            {"backgroundColor", dataToJson(object.backgroundColor)},
            {"promptColor", dataToJson(object.promptColor)}
        };
    }

    template <typename T>
    json dataToJson(const std::vector<T>& vec)
    {
        json jsonArray = json::array();
        for (const auto& item : vec)
        {
            jsonArray.push_back(dataToJson(item));
        }
        return jsonArray;
    }

    template<>
    json dataToJson<saveData>(const saveData& object)
    {
        return json
        {
            {"gameLoopsPlayed", object.gameLoopsPlayed},
            {"failedGuessAttempts", object.failedGuessAttempts},
            {"successfullGuessAttempts", object.successfullGuessAttempts},
            {"timesWon", object.timesWon},
            {"timesLost", object.timesLost},
            {"dumbInputs", object.dumbInputs},
            {"points", object.points},
            {"pointsGainMultiplier", object.pointsGainMultiplier},
            {"pointsDiscountMultiplier", object.pointsDiscountMultiplier},
            {"chosenAttempts", object.chosenAttempts},
            {"guessRange", object.guessRange},
            {"maxAttempts", object.maxAttempts},
            {"difficulty", static_cast<int>(object.difficulty)},
            {"ThemesOwned", dataToJson(object.ThemesOwned)},
            {"currentTheme", dataToJson(object.currentTheme)}
        };
    }

    template <typename T>
    void jsonToData(const json& j, T& output)
    {
        output = j.get<T>();
    }

    template<>
    void jsonToData<Console::TextColor>(const json& j, Console::TextColor& output)
    {
        output = static_cast<Console::TextColor>(j.get<int>());
    }

    template<>
    void jsonToData<Console::BgColor>(const json& j, Console::BgColor& output)
    {
        output = static_cast<Console::BgColor>(j.get<int>());
    }

    template<>
    void jsonToData<Theme>(const json& j, Theme& output)
    {
        output.name = j.value("name", "");
        jsonToData(j["primaryColor"], output.primaryColor);
        jsonToData(j["boldColor"], output.boldColor);
        jsonToData(j["negativeColor"], output.negativeColor);
        jsonToData(j["positiveColor"], output.positiveColor);
        jsonToData(j["lowColor"], output.lowColor);
        jsonToData(j["highColor"], output.highColor);
        jsonToData(j["backgroundColor"], output.backgroundColor);
        jsonToData(j["promptColor"], output.promptColor);
    }

    template <typename T>
    void jsonToData(const json& j, std::vector<T>& vec)
    {
        vec.clear();
        if (j.is_array())
        {
            for (const auto& item : j)
            {
                T element;
                jsonToData(item, element);
                vec.push_back(element);
            }
        }
    }

    template<>
    void jsonToData<saveData>(const json& j, saveData& output)
    {
        output.gameLoopsPlayed = j.value("gameLoopsPlayed", 0);
        output.failedGuessAttempts = j.value("failedGuessAttempts", 0);
        output.successfullGuessAttempts = j.value("successfullGuessAttempts", 0);
        output.timesWon = j.value("timesWon", 0);
        output.timesLost = j.value("timesLost", 0);
        output.dumbInputs = j.value("dumbInputs", 0);
        output.points = j.value("points", 0.0f);
        output.pointsGainMultiplier = j.value("pointsGainMultiplier", 1.0f);
        output.pointsDiscountMultiplier = j.value("pointsDiscountMultiplier", 1.0f);
        output.chosenAttempts = j.value("chosenAttempts", 10);
        output.guessRange = j.value("guessRange", 30);
        output.maxAttempts = j.value("maxAttempts", 10);
        
        if (j.contains("difficulty"))
        {
            output.difficulty = static_cast<DifficultyEnum>(j["difficulty"].get<int>());
        }

        if (j.contains("ThemesOwned"))
        {
            jsonToData(j["ThemesOwned"], output.ThemesOwned);
        }

        if (j.contains("currentTheme"))
        {
            jsonToData(j["currentTheme"], output.currentTheme);
        }
    }
}

bool loadSaveData(const std::string& fileName, saveData& data)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }

    json j;
    file >> j;

    Save::jsonToData(j, data);
    return true;
}

bool saveTempData(const std::string& fileName, const saveData& data)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }

    json j = Save::dataToJson(data);
    file << j.dump(4);
    return true;
}