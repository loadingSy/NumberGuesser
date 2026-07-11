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

struct purchaseInfo
{
    bool accepted = false;
    string purchaseMessage;
};

struct shopItem
{
    int itemId;
    string itemName;
    string description;
    float price;
    function<purchaseInfo()> apply;
    bool purchase()
    { 
        if(tempRunningSaveData.points >= this->price)
        {
            tempRunningSaveData.points -= this->price;
            purchaseInfo purchaseData = apply();
            if(purchaseData.accepted)
            {
                return true;
            }
            
        }
        return false;
    }
};

shopItem item_pointsGainMultiplier;
shopItem item_pointsDiscountMultiplier;

void generateShopItems();

map<int, shopItem> shopItems;

void initializeShop()
{
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
        int validatedInput = validateInput<int>(playerInput);
        if(validatedInput <= 0 or validatedInput > itemsCount)
        {
            cout << "\nInvalid Input\n";
            tempRunningSaveData.dumbInputs++;
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
    item_pointsGainMultiplier.price = 4 * tempRunningSaveData.pointsGainMultiplier * (1-tempRunningSaveData.pointsDiscountMultiplier);
    item_pointsGainMultiplier.apply = []() ->purchaseInfo {
        tempRunningSaveData.pointsGainMultiplier += 0.1;
        saveTempData(fileName, tempRunningSaveData);
        return {true,"accepted"};
    };
    shopItems[item_pointsGainMultiplier.itemId] = (item_pointsGainMultiplier);
}