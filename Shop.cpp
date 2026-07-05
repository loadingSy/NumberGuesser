#include "Shop.h"
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include "SaveLoad.h"
#include "HelperFunctions.h"

using namespace std;

static saveData* globalSaveData = nullptr;



struct shopItem
{
    int itemId;
    string itemName;
    string description;
    float price;
    function<void()> apply;
    bool purchase()
    {
        if(globalSaveData->points >= this->price)
        {
            globalSaveData->points -= this->price;
            apply();
            return true;
        }
        return false;
    }
};

shopItem item_pointsGainMultiplier;


void generateShopItems();

map<int, shopItem> shopItems;

void initializeShop(saveData& saveDataPointer)
{
    globalSaveData = &saveDataPointer;
    generateShopItems();
}


void openShop()
{
    while (true) 
    {
        unordered_map<int, int> inputToId;
        cout << "\nShop\n";
        int itemsCount = 0;
        for (const auto& [id, item] : shopItems) 
        {
            itemsCount++;
            cout << itemsCount << "." << item.itemName << " - " << item.price << "$\n";
            inputToId[itemsCount] = id;
        }
        string playerInput;
        cin >> playerInput;
        int validatedInput = validateToString(playerInput);
        if(validatedInput <= 0 or validatedInput > itemsCount)
        {
            cout << "\nInvalid Input\n";
            globalSaveData->dumbInputs++;
            continue;
        }
        
        if(!shopItems[inputToId[validatedInput]].purchase())
        {
            cout << "\nNot Enough Points!\n";
            continue;
        }
        cout << "\rBought Successfully\n";
        return;
    }
}


void generateShopItems()
{
    item_pointsGainMultiplier.itemName = "Points gain multiplier";
    item_pointsGainMultiplier.itemId = 1133;
    item_pointsGainMultiplier.description = "Multiplier for points generation";
    item_pointsGainMultiplier.price = 4 * globalSaveData->pointsGainMultiplier * (1-globalSaveData->pointsDiscountMultiplier);
    item_pointsGainMultiplier.apply = []() ->void {
        globalSaveData->pointsGainMultiplier += 0.1;
        
        saveTempData(fileName, *globalSaveData);
    };
    shopItems[item_pointsGainMultiplier.itemId] = (item_pointsGainMultiplier);
}