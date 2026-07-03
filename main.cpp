#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <random>

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
};

saveData tempRunningSaveData;

float basePenaltyValue = 5;
int minGuessRange = 10;
int attempts = 10;
int lastDistance = -1;
bool gamePlayInProggress = true;
string fileName = "saveFile.txt";

void returnError(string errorMessage);
int validateInput(string inputToCheck);
void gameLoop();
void triggerDefeat(int rightNumber, int userInput);
int randomInRange(int min, int max);
int validateToString(string stringToCheck);
void endGame(bool victory, int rightNumber);
void mainMenu();
void mainMenuPanelTriggers(int stateId);
void settingsMenu();
void statsMenu();
bool loadSaveData(const string& fileName, saveData& data);
bool saveTempData(const string& fileName, const saveData& data);


int main()
{
    
    if (loadSaveData(fileName, tempRunningSaveData)) 
    {
        cout << "Save data file loaded Successfully!\n";
    }
    else {
        cout << "Save data file Not Found Creating new one...\n";
        if(saveTempData(fileName, tempRunningSaveData))
        {
            cout << "Finished Saving successfully\n";
        }
        else {
            cout << "Saving Failed..\n";
        }
        
    }
    cout << "Press Enter to start: ";
    cin.get();
    mainMenu();
}

void gameLoop()
{
    lastDistance = -1;
    int currentAttempts = tempRunningSaveData.chosenAttempts;
    cout << "Starting Game with:\n"
    << tempRunningSaveData.chosenAttempts << " attempts\n"
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
        int playerGuess = validateInput(playerInput);
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

void mainMenu()
{
    while (true) 
    {
        cout << "\nMain Menu\n"
        <<"1. Play\n"
        <<"2. Settings\n"
        <<"3. Check Stats\n";
        string userInput;
        cin >> userInput;
        int validatedUserInput = validateInput(userInput);
        if(validatedUserInput == -1)
        {
            continue;
        }
        mainMenuPanelTriggers(validatedUserInput);
    }
}

void mainMenuPanelTriggers(int stateId)
{
    switch (stateId) 
    {
        case 1:
        gameLoop();
        break;
        
        case 2:
        settingsMenu();
        break;

        case 3:
        statsMenu();
        break;

        default:
        mainMenu();
        break;
    }
}

int validateToString(string stringToCheck)
{
    try
    {
        int processedInput =  stoi(stringToCheck);
        return processedInput;
    }
    catch (invalid_argument& reason) {
        returnError(reason.what());
        return -1;
    }
    catch (out_of_range& reason)
    {
        returnError(reason.what());
        return -1;
    }
}

int validateInput(string inputToCheck)
{
    try
    {
        int processedInput =  stoi(inputToCheck);
        if(processedInput > tempRunningSaveData.guessRange or processedInput < 0)
        {
            return -1;
        }
        return processedInput;
    }
    catch (invalid_argument& reason) {
        returnError(reason.what());
        return -1;
    }
    catch (out_of_range& reason)
    {
        returnError(reason.what());
        return -1;
    }

}

void returnError(string errorMessage)
{
    cout << "Error happened: " << errorMessage << "\n";
}

void settingsMenu()
{
    while(true)
    {
        cout << "\nSettings\n"
        <<"1. Attempts\n"
        <<"2. Range\n";
        string playerInput;
        cin >> playerInput;

        int validatedInput = validateToString(playerInput);
        if(validatedInput != -1)
        {
            switch (validatedInput) 
            {
                case 1:
                    cout << "\nEnter Attempts Amount (max " << attempts << ", current "<< tempRunningSaveData.chosenAttempts << "): ";
                    playerInput = "";
                    cin >> playerInput;
                    validatedInput = validateToString(playerInput);
                    if(validatedInput < 1)
                    {
                        cout << "\nInvalid input!\n";
                        continue;
                    }
                    if(validatedInput > attempts)
                    {
                        cout << "\nExceeded max of " << attempts << " Setting to " << attempts << "\n";
                        validatedInput = attempts;
                    }

                        cout << "\nSet to: " << validatedInput << " Successfully!\n";
                    tempRunningSaveData.chosenAttempts = validatedInput;
                    return;

                    break;

                case 2:
                    cout << "\nEnter Range 0-N, (current " <<  tempRunningSaveData.guessRange << ", min " << minGuessRange <<"): ";
                    playerInput = "";
                    cin >> playerInput;
                    validatedInput = validateToString(playerInput);
                    if(validatedInput < minGuessRange)
                    {
                        if(validatedInput > 0)
                        {
                            cout << "\nInput lower than minimum: " << minGuessRange << "\n";
                            continue;
                        }
                        cout << "\nInvalid input!\n";
                        continue;
                    }

                    cout << "\nSet to: " << validatedInput << " Successfully!\n";
                    tempRunningSaveData.guessRange = validatedInput;
                    return;
                    break;
            }
            continue;
        }

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
    "Guess Range: 0-" << tempRunningSaveData.guessRange << "\n" <<
    "\n5. To reset: ";
    string playerInput;
    cin >> playerInput;

    int validatedInput = validateToString(playerInput);

    if(validatedInput == 5)
    {
        cout << "\nAre you sure you want to reset your data?\nthis action cant be undone\nType (fffddd) to reset... \n ";
        cin >> playerInput;
        if(playerInput == "fffddd")
        {
            ofstream file(fileName);
            file.trunc;
            file.close();
            loadSaveData(fileName, tempRunningSaveData);
            cout << "\n Reset Succesfully!";
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
    if(victory)
    {
        tempRunningSaveData.timesWon++;
        pointsToChange = ceil((tempRunningSaveData.guessRange * 0.2f - min(min(6.0f,tempRunningSaveData.chosenAttempts*0.1f),tempRunningSaveData.guessRange*0.2f)));
        cout << "You won!, Rewarding \"" << pointsToChange << "\" Points\n";
    }
    else {
        tempRunningSaveData.timesLost++;
        pointsToChange = ceil(-((float)tempRunningSaveData.chosenAttempts/tempRunningSaveData.guessRange*basePenaltyValue));
        cout << "You Lost it was " << rightAnswer << ", Charging \"" << pointsToChange << "\" Points\n" ;
    }

    tempRunningSaveData.points += pointsToChange;
    saveTempData(fileName, tempRunningSaveData);
}

int randomInRange(int min, int max)
{
    random_device dev;
    mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max);
    return dist6(rng);
}

bool loadSaveData(const string& fileName, saveData& data)
{
    ifstream file(fileName);

    if(!file.is_open()) return false;

    file >> data.gameLoopsPlayed;
    file >> data.failedGuessAttempts;
    file >> data.successfullGuessAttempts;
    file >> data.timesWon;
    file >> data.timesLost;
    file >> data.dumbInputs;
    file >> data.points;
    file >> data.pointsGainMultiplier;
    file >> data.pointsDiscountMultiplier;
    file >> data.chosenAttempts;
    file >> data.guessRange;
    

    file.close();
    return true;
}

bool saveTempData(const string& fileName, const saveData& data)
{
    ofstream file(fileName);

    if(!file.is_open()) return false;

    file << data.gameLoopsPlayed << "\n";
    file << data.failedGuessAttempts << "\n";
    file << data.successfullGuessAttempts << "\n";
    file << data.timesWon << "\n";
    file << data.timesLost << "\n";
    file << data.dumbInputs << "\n";
    file << data.points << "\n";
    file << data.pointsGainMultiplier << "\n";
    file << data.pointsDiscountMultiplier << "\n";
    file << data.chosenAttempts << "\n";
    file << data.guessRange << "\n";
    
    file.close();
    return true;
}