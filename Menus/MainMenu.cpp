#include <iostream>
#include <vector>
#include "Menu.h"
#include "../HelperFunctions.h"
#include "../SaveLoad.h"
#include "ShopMenu.h"
#include "SettingsMenu.h"
#include "../GameSettings/GameSettings.h"

void gameLoop();
void triggerDefeat(int rightNumber, int userInput);
void endGame(bool victory, int rightNumber);
void statsMenu();




std::vector<menuTab> mainMenuTabs = 
{
    {"Play", gameLoop},
    {"Shop", [](){ShopMenu.open();}},
    {"Settings", [](){SettingsMenu.open();}},
    {"Check Stats", statsMenu}
};

menu MainMenu("Main Menu",mainMenuTabs);



void gameLoop()
{
    lastDistance = -1;
    int currentAttempts = tempRunningSaveData.chosenAttempts;
    cout << "Starting Game with:\n"
    << tempRunningSaveData.chosenAttempts << " tempRunningSaveData.maxAttempts\n"
    << "0-" << tempRunningSaveData.guessRange << " range\n";
    bool continuePlaying = true;
    bool answeredCorrectly = false;
    int generatedNumber = randomInRange(0, tempRunningSaveData.guessRange);
    while (gamePlayInProggress && continuePlaying) 
    {
        if(!continuePlaying)
        {
            return;
        }
        currentAttempts -= 1;
        cout << "Enter Your Guess: ";
        string playerInput; 
        cin >> playerInput;
        int playerGuess = validateInput<int>(playerInput);
        if(playerGuess > tempRunningSaveData.guessRange or playerGuess < 0)
        {
            playerGuess = -1;
        }
        continuePlaying = currentAttempts > 0 && (playerGuess == -1 or playerGuess != generatedNumber);
        if(playerGuess == -1 or playerGuess != generatedNumber)
        {
            triggerDefeat(generatedNumber, playerGuess);
            continue;
        }
        
        
        answeredCorrectly = true;
        tempRunningSaveData.successfullGuessAttempts++;
    }


    endGame(answeredCorrectly, generatedNumber);
}


void settingsMenu()
{
    while(true)
    {
        
        string playerInput;
        cin >> playerInput;

        int validatedInput = validateInput<int>(playerInput);
        

        cout << "\nInvalid Input! retry again.\n";
    }

    cout << "Input correct";
}

void statsMenu()
{
    // adding save using I/O maybe a bit later
    cout << "\nStats\n";
    cout << "Game Loops Played: " << tempRunningSaveData.gameLoopsPlayed << "\n" <<
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
    "\n5. To reset: ";
    string playerInput;
    cin >> playerInput;

    int validatedInput = validateInput<int>(playerInput);

    if(validatedInput == 5)
    {
        cout << "\nAre you sure you want to reset your data?\nthis action cant be undone\nType (fffddd) to reset... \n ";
        cin >> playerInput;
        if(playerInput == "fffddd")
        {
            tempRunningSaveData = saveData();
            saveTempData(fileName, tempRunningSaveData);
            cout << "\n Reset Successfully!";
        }
    }
    cout << "\nPress Enter to return to menu ";
}

void triggerDefeat(int rightNumber, int userInput)
{
    tempRunningSaveData.failedGuessAttempts++;
    string messageOutput;
    string typeOutput = "";
    if(userInput == -1)
    {
        messageOutput = "Your input is Invalid\nPress enter to continue... ";
        tempRunningSaveData.dumbInputs++;
        cin.get();
    }
    else
    {
        int distance = abs(userInput - rightNumber);
        int percentageDifference = (distance * 100) / tempRunningSaveData.guessRange;
        
        

        if (lastDistance == -1)
        {
            if (userInput > rightNumber) 
            {
                typeOutput = "High!";
            } 
            else 
            {
                typeOutput = "Low!";
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
                typeOutput = "Colder";
            }
            else 
            {
                typeOutput = "Hotter";
            }
            
            int differenceInGuess = max(percentageDifference,lastDistance) - min(percentageDifference,lastDistance);
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
    }

    

    cout << messageOutput << typeOutput <<"\n";
    
}

void endGame(bool victory, int rightAnswer)
{
    tempRunningSaveData.gameLoopsPlayed++;
    float pointsToChange = 0.0f;
    float tempPointsToChange;
    if(victory)
    {
        tempPointsToChange = (tempRunningSaveData.guessRange * 0.6f - min(min(6.0f,tempRunningSaveData.chosenAttempts*0.1f),tempRunningSaveData.guessRange*0.2f));
    }
    else 
    {
        tempPointsToChange = -((float)tempRunningSaveData.chosenAttempts/tempRunningSaveData.guessRange*basePenaltyValue);
    }

    pointsToChange = tempPointsToChange*tempRunningSaveData.pointsGainMultiplier;

    if(victory)
    {
        tempRunningSaveData.timesWon++;
        cout << "You won!, Rewarding \"" << pointsToChange << "\" Points\n";
    }
    else {
        tempRunningSaveData.timesLost++;
        cout << "You Lost it was " << rightAnswer << ", Charging \"" << pointsToChange << "\" Points\n" ;
    }

    tempRunningSaveData.points += pointsToChange;
    saveTempData(fileName, tempRunningSaveData);
}
