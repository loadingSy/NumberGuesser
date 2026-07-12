#pragma once

#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "Menu.h"
#include "../GameSettings/GameSettings.h"
#include "../SaveLoad.h"

struct purchaseInfo
{
    purchaseInfo(bool cResult, std::optional<std::string> cMessage)
    : accepted(cResult), message(cMessage) {}
    bool accepted = true;
    std::optional<std::string> message;    
};

class shopItem
{
    public:
        shopItem(std::string cName, float cPrice, std::function<purchaseInfo()> cApply)
        : name(cName), price(cPrice), apply(cApply) {}
        std::string name = "";
        float price = 0;
        bool available = true;
        bool purchase()
        {
            if(tempRunningSaveData.points >= price)
            {
                purchaseInfo appliedData = apply();
                if(appliedData.accepted)
                {
                    tempRunningSaveData.points -= price;
                    return true;
                }                                
            }
            return false;
        }
    private:
        std::function<purchaseInfo()> apply;

};



extern menu ShopMenu;
