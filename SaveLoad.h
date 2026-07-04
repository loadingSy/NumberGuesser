#pragma once

#include <string>

using namespace std;

struct saveData
{
    int gameLoopsPlayed = 0;
    int failedGuessAttempts = 0;
    int successfullGuessAttempts = 0;
    int timesWon = 0;
    int timesLost = 0;
    int dumbInputs = 0;
    int points = 0;
    int pointsGainMultiplier = 1;
    int pointsDiscountMultiplier = 1;
    int chosenAttempts = 10;
    int guessRange = 30;
    int maxAttempts = 10;
};

bool loadSaveData(const string& fileName, saveData& data);

bool saveTempData(const string& fileName, const saveData& data);
