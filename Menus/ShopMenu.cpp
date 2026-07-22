#include "ShopMenu.h"
#include <cmath>
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

inline std::string generateItemNameStructure(shopItem item)
{
    std::stringstream ss;
    ss << item.name << " - " << item.getPrice() << "$";
    return ss.str();
}

std::vector<menuTab> shopTabs = 
{
    
};

std::vector<shopItem> shopItems;

menu ShopMenu("Shop", std::ref(shopTabs), true, initializeShop);

shopItem pointsGainMultiplier("Points Gain Multiplier", [](){ return pow(10 * tempRunningSaveData.pointsGainMultiplier,1.15);}, 
[]()->purchaseInfo
{
    tempRunningSaveData.pointsGainMultiplier+=0.2;
    return {true, std::nullopt};
}
);

void managePurchase(shopItem item)
{
    float price = item.getPrice();
    purchaseInfo info = item.purchase();
    bool result = info.accepted;
    if(result)
    {
        if(info.message.has_value())
        {
            std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.boldColor) << info.message.value();
        }
        else
        {
            std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.positiveColor) << "Purchased Successfully for " << price << "$";
            saveTempData(fileName, tempRunningSaveData);
        }
    }
    else 
    {
        if(info.message.has_value())
        {
            std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.negativeColor) << info.message.value();
        }
        else
        {
            std::cout << Console::getStyleString(tempRunningSaveData.currentTheme.negativeColor) << "Failed for unknown reason\n";
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