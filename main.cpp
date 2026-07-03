#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <random>

using namespace std;

float basePenaltyValue = 5;
int minGuessRange = 10;
int guessRange = 30;
int points = 0;
int pointsGainMultiplier = 1;
int pointsDiscountMultiplier = 1;
int attempts = 10;
int chosenAttempts = 10;
int lastDistance = -1;
bool gamePlayInProggress = true;

void returnError(string errorMessage);
int validateInput(string inputToCheck);
void gameLoop();
void triggerDefeat(int rightNumber, int userInput);
int randomInRange(int min, int max);
int validateToString(string stringToCheck);
void endGame(bool victory);
void mainMenu();
void mainMenuPanelTriggers(int stateId);
void settingsMenu();


int main()
{
    cout << "Press Enter to start: ";
    cin.get();
    mainMenu();
}

void gameLoop()
{
    lastDistance = -1;
    int currentAttempts = chosenAttempts;
    cout << "Starting Game with:\n"
    << chosenAttempts << " attempts\n"
    << "0-" << guessRange << " range\n";
    bool continuePlaying = true;
    bool answeredCorrectly = false;
    int generatedNumber = randomInRange(11, guessRange);
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
    }

    endGame(answeredCorrectly);
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

        default:
        mainMenu();
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
        if(processedInput > guessRange or processedInput < 0)
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
                    cout << "\nEnter Attempts Amount (max " << attempts << ", current "<< chosenAttempts << "): ";
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
                    chosenAttempts = validatedInput;
                    return;

                    break;

                case 2:
                    cout << "\nEnter Range 0-N, (current " <<  guessRange << ", min " << minGuessRange <<"): ";
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
                    return;
                    break;
            }
            continue;
        }

        cout << "\nInvalid Input! retry again.\n";
    }

    cout << "Input correct";
}

void triggerDefeat(int rightNumber, int userInput)
{
    string messageOutput;
    string typeOutput = "";
    if(userInput == -1)
    {
        messageOutput = "Your input is Invalid\nPress enter to continue... ";
        cin.get();
    }
    else
    {
        int distance = abs(userInput - rightNumber);
        int percentageDifference = (distance * 100) / guessRange;
        
        

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
                messageOutput = "You are Burning but ";
            }
            else if (differenceInGuess <= 10) 
            {
            messageOutput = "You are only a bit ";
            } else if (differenceInGuess <= 25) 
            {
                messageOutput = "You are ";
            } else if (differenceInGuess <= 50) 
            {
                messageOutput = "You are Very ";
            } else 
            {
                messageOutput = "You are Extremely ";
            }
            
        }
        lastDistance = percentageDifference;
    }

    

    cout << messageOutput << typeOutput <<"\n";
    cin.get();
}

void endGame(bool victory)
{
    float pointsToChange = 0.0f;
    if(victory)
    {
        pointsToChange = ceil((guessRange * 0.2f - min(min(6.0f,chosenAttempts*0.1f),guessRange*0.2f)));
        cout << "You won!, Rewarding \"" << pointsToChange << "\" Points\n";
    }
    else {
        pointsToChange = ceil(-((float)chosenAttempts/guessRange*basePenaltyValue));
        cout << "You Lost, Charging \"" << pointsToChange << "\"Points\n" ;
    }

    points += pointsToChange;
}

int randomInRange(int min, int max)
{
    random_device dev;
    mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max);
    return dist6(rng);
}