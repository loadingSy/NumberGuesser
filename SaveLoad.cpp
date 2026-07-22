#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "SaveLoad.h"

using namespace std;


int saveVersion = 2344436;
string fileName = "saveFile.txt";

saveData tempRunningSaveData;

namespace
{
    bool readTheme(std::istream& in, Theme& theme)
    {
        int primary = 0;
        int bold = 0;
        int negative = 0;
        int positive = 0;
        int low = 0;
        int high = 0;
        int background = 0;
        int prompt = 0;

        return static_cast<bool>(
            in >> std::quoted(theme.name)
               >> primary
               >> bold
               >> negative
               >> positive
               >> low
               >> high
               >> background
               >> prompt
        ) && (
            theme.primaryColor = static_cast<Console::TextColor>(primary),
            theme.boldColor = static_cast<Console::TextColor>(bold),
            theme.negativeColor = static_cast<Console::TextColor>(negative),
            theme.positiveColor = static_cast<Console::TextColor>(positive),
            theme.lowColor = static_cast<Console::TextColor>(low),
            theme.highColor = static_cast<Console::TextColor>(high),
            theme.backgroundColor = static_cast<Console::BgColor>(background),
            theme.promptColor = static_cast<Console::TextColor>(prompt),
            true
        );
    }

    void writeTheme(std::ostream& out, const Theme& theme)
    {
        out << std::quoted(theme.name) << ' '
            << static_cast<int>(theme.primaryColor) << ' '
            << static_cast<int>(theme.boldColor) << ' '
            << static_cast<int>(theme.negativeColor) << ' '
            << static_cast<int>(theme.positiveColor) << ' '
            << static_cast<int>(theme.lowColor) << ' '
            << static_cast<int>(theme.highColor) << ' '
            << static_cast<int>(theme.backgroundColor) << ' '
            << static_cast<int>(theme.promptColor) << '\n';
    }
}

bool loadSaveData(const string& fileName, saveData& data)
{
    ifstream file(fileName);

    if(!file.is_open()) return false;

    int loadedVersion = 0;
    file >> loadedVersion;
    if(!file)
    {
        data = saveData();
        return false;
    }
    
    if(loadedVersion != saveVersion)
    {
        cout << "Outdated save file detected! Resetting to defaults.\n";
        data = saveData();
        return false;
    }
    
    int difficultyValue = 0;
    size_t themeCount = 0;

    file >> data.gameLoopsPlayed
         >> data.failedGuessAttempts
         >> data.successfullGuessAttempts
         >> data.timesWon
         >> data.timesLost
         >> data.dumbInputs
         >> data.points
         >> data.pointsGainMultiplier
         >> data.pointsDiscountMultiplier
         >> data.chosenAttempts
         >> data.guessRange
         >> data.maxAttempts
         >> difficultyValue
         >> themeCount;

    if(!file)
    {
        data = saveData();
        return false;
    }

    data.difficulty = static_cast<DifficultyEnum>(difficultyValue);
    data.ThemesOwned.clear();
    data.ThemesOwned.reserve(themeCount);

    for(size_t i = 0; i < themeCount; ++i)
    {
        Theme theme;
        if(!readTheme(file, theme))
        {
            data = saveData();
            return false;
        }
        data.ThemesOwned.push_back(theme);
    }

    if(!readTheme(file, data.currentTheme))
    {
        data = saveData();
        return false;
    }

    return true;
}

bool saveTempData(const string& fileName, const saveData& data)
{
    ofstream file(fileName);

    if(!file.is_open()) return false;

    file << saveVersion << '\n'
         << data.gameLoopsPlayed << ' '
         << data.failedGuessAttempts << ' '
         << data.successfullGuessAttempts << ' '
         << data.timesWon << ' '
         << data.timesLost << ' '
         << data.dumbInputs << ' '
         << data.points << ' '
         << data.pointsGainMultiplier << ' '
         << data.pointsDiscountMultiplier << ' '
         << data.chosenAttempts << ' '
         << data.guessRange << ' '
         << data.maxAttempts << ' '
         << static_cast<int>(data.difficulty) << ' '
         << data.ThemesOwned.size() << '\n';

    for(const auto& theme : data.ThemesOwned)
    {
        writeTheme(file, theme);
    }

    writeTheme(file, data.currentTheme);

    return true;
}
