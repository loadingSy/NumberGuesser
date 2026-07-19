#include <iostream>
#include <vector>
#include "Menu.h"
#include "../HelperFunctions.h"
#include "../SaveLoad.h"
#include "ShopMenu.h"
#include "SettingsMenu.h"
#include "../GameSettings/GameSettings.h"
#include "GameLoop.h"

void statsMenu();




std::vector<menuTab> mainMenuTabs = 
{
    {"Play", [](){GameMenu.open();}},
    {"Shop", [](){ShopMenu.open();}},
    {"Settings", [](){SettingsMenu.open();}},
    {"Check Stats", statsMenu}
};

menu MainMenu("Main Menu",mainMenuTabs,true);


void statsMenu()
{
    // adding save using I/O maybe a bit later
    std::cout << "\nStats\n";
    std::cout << "Game Loops Played: " << tempRunningSaveData.gameLoopsPlayed << "\n" <<
    "Failed Guesses: " << tempRunningSaveData.failedGuessAttempts << "\n" <<
    "Successfull Guesses: " << tempRunningSaveData.successfullGuessAttempts << "\n" <<
    "Times Won: " << tempRunningSaveData.timesWon << "\n" <<
    "Times Lost: " << tempRunningSaveData.timesLost << "\n" <<
    "Dumb inputs: " << tempRunningSaveData.dumbInputs << "\n" <<
    "Points: " << tempRunningSaveData.points << "\n" <<
    "Points Gain Multiplier: " << tempRunningSaveData.pointsGainMultiplier << "\n" <<
    "Points Discount Multiplier: " << tempRunningSaveData.pointsDiscountMultiplier << "\n" <<
    "Chosen Attempts: " << tempRunningSaveData.chosenAttempts << "\n" <<
    "Max Attempts" << tempRunningSaveData.maxAttempts << "\n" <<
    "Guess Range: 0-" << tempRunningSaveData.guessRange << "\n" <<
    "Difficulty: " << tempRunningSaveData.difficulty <<
    "\n5. To reset: ";
    std::string playerInput;
    std::cin >> playerInput;

    int validatedInput = validateInput<int>(playerInput);

    if(validatedInput == 5)
    {
        std::cout << "\nAre you sure you want to reset your data?\nthis action cant be undone\nType (fffddd) to reset... \n ";
        std::cin >> playerInput;
        if(playerInput == "fffddd")
        {
            tempRunningSaveData = saveData();
            saveTempData(fileName, tempRunningSaveData);
            std::cout << "\n Reset Successfully!";
        }
    }
    std::cout << "\nPress Enter to return to menu ";
}

