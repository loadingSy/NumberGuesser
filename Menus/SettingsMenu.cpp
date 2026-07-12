#include <iostream>
#include <sstream>
#include <vector>
#include "Menu.h"
#include "../HelperFunctions.h"
#include "../SaveLoad.h"
#include "ShopMenu.h"
#include "../GameSettings/GameSettings.h"

void attemptsFunction()
{
    stringstream inputSS;
    inputSS << "\nEnter Attempts Amount (max " << tempRunningSaveData.maxAttempts << ", current "<< tempRunningSaveData.chosenAttempts << "): ";
    string inputQuestion = inputSS.str();
    int validatedInput = ask<int>(inputQuestion);
                    if(validatedInput < 1)
                    {
                        cout << "\nInvalid input!\n";
                        return;
                    }
                    if(validatedInput > tempRunningSaveData.maxAttempts)
                    {
                        cout << "\nExceeded max of " << tempRunningSaveData.maxAttempts << " Setting to " << tempRunningSaveData.maxAttempts << "\n";
                        validatedInput = tempRunningSaveData.maxAttempts;
                    }
                        cout << "\nSet to: " << validatedInput << " Successfully!\n";
                    tempRunningSaveData.chosenAttempts = validatedInput;
                    return;
}

void rangeFunction()
{
    stringstream inputSS;
    inputSS <<  "\nEnter Range 0-N, (current " <<  tempRunningSaveData.guessRange << ", min " << minGuessRange <<"): ";
    string inputQuestion = inputSS.str();
    int validatedInput = ask<int>(inputQuestion);
    if(validatedInput < minGuessRange)
    {
        if(validatedInput > 0)
        {
            cout << "\nInput lower than minimum: " << minGuessRange << "\n";
            return;
        }
        cout << "\nInvalid input!\n";
        return;
    }

    cout << "\nSet to: " << validatedInput << " Successfully!\n";
    tempRunningSaveData.guessRange = validatedInput;
    return;
}

std::vector<menuTab> settingsMenuTabs = 
{
    {"Attempts", attemptsFunction},
    {"Range", rangeFunction},
    {"Idk", std::vector<menuTab>
        {
        {"Hey", std::vector<menuTab>
            {
                {"raur", attemptsFunction},
                {"raur2",attemptsFunction}

            }
        },
        {"Hey2",attemptsFunction},
        }
}
};

menu SettingsMenu("Settings", settingsMenuTabs);

