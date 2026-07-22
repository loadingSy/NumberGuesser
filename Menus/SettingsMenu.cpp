#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Menu.h"
#include "../HelperFunctions.h"
#include "../SaveLoad.h"
#include "ShopMenu.h"
#include "../GameSettings/GameSettings.h"
#include "ThemesMenu.h"

void attemptsFunction()
{
    std::stringstream inputSS;
    inputSS << "\nEnter Attempts Amount (max " << tempRunningSaveData.maxAttempts << ", current "<< tempRunningSaveData.chosenAttempts << "): ";
    std::string inputQuestion = inputSS.str();
    int validatedInput = ask<int>(inputQuestion);
                    if(validatedInput < 1)
                    {
                        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.negativeColor) << "\nInvalid input!\n";
                        return;
                    }
                    if(validatedInput > tempRunningSaveData.maxAttempts)
                    {
                        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.negativeColor) << "\nExceeded max of " << tempRunningSaveData.maxAttempts << " Setting to " << tempRunningSaveData.maxAttempts << "\n";
                        validatedInput = tempRunningSaveData.maxAttempts;
                    }
                        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << "\nSet to: " << validatedInput << " Successfully!\n";
                    tempRunningSaveData.chosenAttempts = validatedInput;
                    return;
}

void rangeFunction()
{
    std::stringstream inputSS;
    inputSS <<  "\nEnter Range 0-N, (current " <<  tempRunningSaveData.guessRange << ", min " << minGuessRange <<"): ";
    std::string inputQuestion = inputSS.str();
    int validatedInput = ask<int>(inputQuestion);
    if(validatedInput < minGuessRange)
    {
        if(validatedInput > 0)
        {
            std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.negativeColor) << "\nInput lower than minimum: " << minGuessRange << "\n";
            return;
        }
        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.negativeColor) << "\nInvalid input!\n";
        return;
    }

    std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << "\nSet to: " << validatedInput << " Successfully!\n";
    tempRunningSaveData.guessRange = validatedInput;
    return;
}


std::vector<menuTab> settingsMenuTabs = 
{
    {"Attempts", attemptsFunction},
    {"Range", rangeFunction},
    {"Themes", [](){themesMenu.open();}}
};

menu SettingsMenu("Settings", settingsMenuTabs);

