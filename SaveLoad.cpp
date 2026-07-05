#include <string>
#include <iostream>
#include <fstream>
#include "SaveLoad.h"

using namespace std;


int saveVersion = 1;
string fileName = "saveFile.txt";



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