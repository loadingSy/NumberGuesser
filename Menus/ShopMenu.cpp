#include "ShopMenu.h"
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "../SaveLoad.h"
#include "../HelperFunctions.h"
#include "../GameSettings/GameSettings.h"
#include "Menu.h"


void initializeShop();

inline string generateItemNameStructure(shopItem item)
{
    stringstream ss;
    ss << item.name << " - " << item.price << "$";
    return ss.str();
}

std::vector<menuTab> shopTabs = 
{
    
};

std::vector<shopItem> shopItems;

menu ShopMenu("Shop", std::ref(shopTabs), true, initializeShop);

shopItem pointsGainMultiplier("Points Gain Multiplier", 10*tempRunningSaveData.pointsGainMultiplier, 
[]()->purchaseInfo
{
    tempRunningSaveData.pointsGainMultiplier+=0.1;
    pointsGainMultiplier.price++;
    return {true, std::nullopt};
}
);

void managePurchase(shopItem item)
{
    purchaseInfo info = item.purchase();
    bool result = info.accepted;
    if(result)
    {
        if(info.message.has_value())
        {
            cout << info.message.value();
        }
        else
        {
            cout << "Purchased Successfully for " << item.price << "$";
        }
    }
    else 
    {
        if(info.message.has_value())
        {
            cout << info.message.value();
        }
        else
        {
            cout << "Failed for unknown reason\n";
        }
    }
    shopTabs[item.index].name = generateItemNameStructure(item);
}

void initializeShop()
{
    shopItems.clear();
    shopTabs.clear();
    
    shopItems.push_back(pointsGainMultiplier);
    

    for(size_t i = 0; i < shopItems.size(); ++i)
    {
        shopItems[i].index = i;
        menuTab tempTab(generateItemNameStructure(shopItems[i]),[i](){managePurchase(shopItems[i]);});
        shopTabs.push_back(tempTab);
    } 
}
//to be added price getter/setter
