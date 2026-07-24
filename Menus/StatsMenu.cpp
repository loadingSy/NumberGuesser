#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Menu.h"
#include "../SaveLoad.h"
#include "StatsMenu.h"

void showStats();
void resetStats();

std::vector<menuTab> statsTabs = 
{
    {"Show Stats",showStats},
    {"Reset Stats",resetStats}
};

menu StatsMenu("Stats",statsTabs,true);


void showStats()
{
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
    "Difficulty: " << tempRunningSaveData.difficulty;
    std::cin.clear();
    std::cin.ignore();
    std::cin.get();
}

void resetStats()
{
    std::string playerInput = ask<std::string>("\nAre you sure you want to reset your data?\nthis action cant be undone\nType (fffddd) to reset... \n ");

    if(playerInput == "fffddd")
    {
        tempRunningSaveData = saveData();
        saveTempData(saveFileName, tempRunningSaveData);
        std::cout << "\n Reset Successfully!";
    }
}