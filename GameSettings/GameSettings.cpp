#include <iostream>
#include "GameSettings.h"
#include "../SaveLoad.h"
#include <array>
#include <vector>

float basePenaltyValue = 5;
int minGuessRange = 10;
int lastDistance = -1;


std::vector<std::array<int, 2>> difficultySettings =
{
    {20,7},
    {30,5},
    {40,6}
};