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
menu ShopMenu("Shop", shopTabs, true, initializeShop);

std::vector<shopItem> shopItems;

shopItem pointsGainMultiplier("Points Gain Multiplier", 10, 
[]()->purchaseInfo
{
    tempRunningSaveData.pointsGainMultiplier+=0.1;
    pointsGainMultiplier.price++;
    return {true, nullopt};
}
);

void managePurchase(shopItem item)
{

}

void initializeShop()
{
    shopItems.push_back(pointsGainMultiplier);
    

    for(auto& item : shopItems)
    {
        menuTab tempTab(item.name,[item](){managePurchase(item);});
        shopTabs.push_back(tempTab);
    }
}
// very buggy and compile errors will be fixed later
//intialization order problems too :)
