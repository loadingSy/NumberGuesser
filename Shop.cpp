#include "Shop.h"
#include <_mingw_stat64.h>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include "SaveLoad.h"

using namespace std;

unordered_map<int, function<bool()>> shopItemsFunctions;

static saveData* globalSaveData = nullptr;



struct shopItem
{
    int itemId;
    string itemName;
    string description;
    int price;
};

shopItem item_pointsGainMultiplier;


void generateShopItems();

list<shopItem> shopItems;

void intializeShop(saveData& saveDataPointer)
{
    globalSaveData = &saveDataPointer;
    generateShopItems();
}


void openShop(int& points)
{
    cout << "\nShop\n";
    
    
}


void generateShopItems()
{
    item_pointsGainMultiplier.itemName = "Points gain multiplier";
    item_pointsGainMultiplier.itemId = 1133;
    item_pointsGainMultiplier.description = "Multiplier for points generation";
    item_pointsGainMultiplier.price = globalSaveData->pointsGainMultiplier*4;

    shopItemsFunctions[item_pointsGainMultiplier.itemId] = [](){
        globalSaveData->pointsGainMultiplier += 0.1;
        globalSaveData->points -= item_pointsGainMultiplier.price;
        
        return true;
    };
}