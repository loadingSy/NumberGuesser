#pragma once

#include <string>

using namespace std;


extern string fileName;

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
};

bool loadSaveData(const string& fileName, saveData& data);

bool saveTempData(const string& fileName, const saveData& data);
