#include "Menu.h"
#include "../GameSettings/GameSettings.h"
#include "../SaveLoad.h"
#include <array>
#include <iostream>
#include <vector>
#include <string>


void gameLoop();
void triggerDefeat(int rightNumber, int userInput, std::array<int, 2> gameSettings);
void endGame(bool victory, int rightNumber, std::array<int, 2> gameSettings);

std::string getDifficulty()
{
    switch (tempRunningSaveData.difficulty) 
    {
        case 0:
            return "Easy";
            break;
        case 1:
            return "Medium";
            break;
        case 2:
            return "Hard";
            break;
        case 3:
            return "Custom";
            break;
    }
    return "None";
}

inline void setDifficulty(int diff);

std::vector<menuTab> difficultyTabs = 
{
    {"Easy",[]{setDifficulty(0);}},
    {"Medium",[]{setDifficulty(1);}},
    {"Hard",[]{setDifficulty(2);}},
    {"Custom",[]{setDifficulty(3);}},
};

std::vector<menuTab> gameTabs =
{
    {std::string("Start Game"),gameLoop},
    {std::string("Change Preset - ")+getDifficulty(),difficultyTabs}
    
};

inline void setDifficulty(int diff)
{
    tempRunningSaveData.difficulty = static_cast<DifficultyEnum>(diff);
    saveTempData(fileName, tempRunningSaveData);
    gameTabs[1].name = "Change Preset - "+getDifficulty();
}

void initializeGame();

menu GameMenu("Game Menu",gameTabs, true,initializeGame);

void initializeGame()
{
    gameTabs[1].name = "Change Preset - "+getDifficulty();
}


void gameLoop()
{
    lastDistance = -1;
    int startAttempts = (tempRunningSaveData.difficulty == 3 ? tempRunningSaveData.chosenAttempts : difficultySettings[tempRunningSaveData.difficulty][1]);
    int currentAttempts = startAttempts;
    int currentRange = (tempRunningSaveData.difficulty == 3 ? tempRunningSaveData.guessRange : difficultySettings[tempRunningSaveData.difficulty][0]);
    std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.primaryColor) << "Starting Game with:\n"
    << currentAttempts << " Attempts\n"
    << "0-" << currentRange << " range\n";
    bool continuePlaying = true;
    bool answeredCorrectly = false;
    int generatedNumber = randomInRange(0, currentRange);
    while (continuePlaying) 
    {
        if(!continuePlaying)
        {
            return;
        }
        currentAttempts -= 1;
        bool acceptedInput = false;
        int playerGuess;
        while (!acceptedInput) 
        {
            playerGuess = ask<int>("Enter Your Guess: ");
            acceptedInput = inRange(playerGuess, 0, currentRange);
        }
        continuePlaying = currentAttempts > 0 && (playerGuess != generatedNumber);
        if(playerGuess != generatedNumber)
        {
            triggerDefeat(generatedNumber, playerGuess, {currentRange,startAttempts});
            continue;
        }
        
        
        answeredCorrectly = true;
        tempRunningSaveData.successfullGuessAttempts++;
    }


    endGame(answeredCorrectly, generatedNumber, {currentRange,startAttempts});
}

void triggerDefeat(int rightNumber, int userInput, std::array<int, 2> gameSettings)
{
    tempRunningSaveData.failedGuessAttempts++;
    std::string messageOutput;
    std::string typeOutput = "";

    int distance = abs(userInput - rightNumber);
    int percentageDifference = (distance * 100) / gameSettings[0];
    
    if (lastDistance == -1)
    {
        if (userInput > rightNumber) 
        {
            typeOutput = Console::getStyleString(tempRunningSaveData.currentTheme.highColor) + "High!";
        } 
        else 
        {
            typeOutput = Console::getStyleString(tempRunningSaveData.currentTheme.lowColor) + "Low!";
        }

        
        if (percentageDifference <= 10) 
        {
        messageOutput = "You are only a bit ";
        } else if (percentageDifference <= 25) 
        {
            messageOutput = "You are ";
        } else if (percentageDifference <= 50) 
        {
            messageOutput = "You are Very ";
        } else 
        {
            messageOutput = "You are Extremely ";
        }
    }
    else 
    {
        if (percentageDifference > lastDistance) 
        {

            typeOutput = Console::getStyleString(tempRunningSaveData.currentTheme.highColor) + "Colder";
        }
        else 
        {
            typeOutput = Console::getStyleString(tempRunningSaveData.currentTheme.lowColor) + "Hotter";
        }
        
        int differenceInGuess = std::max(percentageDifference,lastDistance) - std::min(percentageDifference,lastDistance);
        if (differenceInGuess == 0)
        {
            typeOutput = "";
            messageOutput = "No Change~";
        }
        else if (percentageDifference <= 10)
        {
            messageOutput = "You are Very Close, but getting ";
        }
        else if (differenceInGuess <= 10) 
        {
        messageOutput = "You are only getting a bit ";
        } else if (differenceInGuess <= 25) 
        {
            messageOutput = "You are getting ";
        } else if (differenceInGuess <= 50) 
        {
            messageOutput = "You are getting Very ";
        } else 
        {
            messageOutput = "You are getting Extremely ";
        }
        
    }
    lastDistance = percentageDifference;

    

    std::cout << messageOutput << typeOutput <<"\n";
    
}

void endGame(bool victory, int rightAnswer, std::array<int, 2> gameSettings)
{
    tempRunningSaveData.gameLoopsPlayed++;
    float pointsToChange = 0.0f;
    float tempPointsToChange;
    int currentRange = gameSettings[0];
    int currentAttempts = gameSettings[1];
    if(victory)
    {
        tempPointsToChange = (currentRange * 0.6f - std::min(std::min(6.0f,currentAttempts*0.1f),currentRange*0.2f));
    }
    else 
    {
        tempPointsToChange = -((float)currentAttempts/currentRange*basePenaltyValue);
    }

    pointsToChange = tempPointsToChange*tempRunningSaveData.pointsGainMultiplier;

    if(victory)
    {
        tempRunningSaveData.timesWon++;
        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << "You won!, Rewarding \"" << pointsToChange << "\" Points\n";
    }
    else {
        tempRunningSaveData.timesLost++;
        std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.negativeColor) << "You Lost it was " << rightAnswer << ", Charging \"" << pointsToChange << "\" Points\n" ;
    }

    tempRunningSaveData.points += pointsToChange;
    saveTempData(fileName, tempRunningSaveData);
}
