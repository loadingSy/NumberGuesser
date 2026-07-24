#include "SaveLoad.h"
#include "ConsoleTypes.h"

std::string saveFileName = "SaveData/saveFile.json";
saveData tempRunningSaveData;

bool loadSaveData(const std::string& saveFileName, saveData& data)
{
    return loadFromFile(saveFileName, data);
}

bool saveTempData(const std::string& saveFileName, const saveData& data)
{
    return saveToFile(saveFileName, data);
}