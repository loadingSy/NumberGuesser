#include <string>
#include <iostream>
#include <fstream>


using namespace std;


int saveVersion = 1;

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

bool loadSaveData(const string& fileName, saveData& data)
{
    ifstream file(fileName, ios::binary);

    if(!file.is_open()) return false;

    int loadedVersion = 0;
    file.read(reinterpret_cast<char*>(&loadedVersion), sizeof(loadedVersion));
    
    if(loadedVersion != saveVersion)
    {
        cout << "Outdated save file detected! Resetting to defaults.\n";
        data = saveData(); // Reset the struct to 0/defaults
        file.close();
        return false;
    }
    
    file.read(reinterpret_cast<char*>(&data), sizeof(data));


    file.close();
    return true;
}

bool saveTempData(const string& fileName, const saveData& data)
{
    ofstream file(fileName, ios::binary);

    if(!file.is_open()) return false;

    
    file.write(reinterpret_cast<const char*>(&saveVersion), sizeof(saveVersion));
    file.write(reinterpret_cast<const char*>(&data), sizeof(data));


    
    file.close();
    return true;
}