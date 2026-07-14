#include "ShopMenu.h"
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "../SaveLoad.h"
#include "../HelperFunctions.h"
#include "../GameSettings/GameSettings.h"
#include "Menu.h"


void initializeShop();

std::vector<menuTab> shopTabs = 
{
    
};

std::vector<shopItem> shopItems;

menu ShopMenu("Shop", std::ref(shopTabs), true, initializeShop);

shopItem pointsGainMultiplier("Points Gain Multiplier", 10, 
[]()->purchaseInfo
{
    tempRunningSaveData.pointsGainMultiplier+=0.1;
    pointsGainMultiplier.price++;
    return {true, std::nullopt};
}
);

void managePurchase(shopItem item)
{

}

void initializeShop()
{
    shopItems.clear();
    shopTabs.clear();
    
    shopItems.push_back(pointsGainMultiplier);
    

    for(size_t i = 0; i < shopItems.size(); ++i)
    {
        menuTab tempTab(shopItems[i].name,[i](){managePurchase(shopItems[i]);});
        shopTabs.push_back(tempTab);
    } 
}
