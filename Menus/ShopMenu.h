#pragma once

#include <cstddef>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <variant>
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
        shopItem(std::string cName, int cPrice, std::function<purchaseInfo()> cApply)
        : name(cName), price(cPrice), apply(cApply) {}
        shopItem(std::string cName, std::function<float()> cPrice, std::function<purchaseInfo()> cApply)
        : name(cName), price(cPrice), apply(cApply) {}
        shopItem(std::string cName, std::function<int()> cPrice, std::function<purchaseInfo()> cApply)
        : name(cName), price(cPrice), apply(cApply) {}
        
        std::string name = "";
        std::variant<float, int, std::function<float()>, std::function<int()>> price;
        int index;
        bool available = true;
        purchaseInfo purchase()
        {
            float curPrice;
            int priceIndex = price.index();
            switch (priceIndex) 
            {
                case 0:
                    curPrice = std::get<0>(price);
                    break;
                case 1:
                    curPrice = std::get<1>(price);
                    break;
                case 2:
                    curPrice = std::get<2>(price)();
                    break;
                case 3:
                    curPrice = std::get<3>(price)();    
                    break;
                default:
                    return;
            }
            if(tempRunningSaveData.points >= curPrice)
            {
                purchaseInfo appliedData = apply();
                if(appliedData.accepted)
                {
                    tempRunningSaveData.points -= curPrice;
                    return appliedData;
                }
                return {false, nullopt};
            }
            return {false, "Not enough Points"};
        }
    private:
        std::function<purchaseInfo()> apply;

};



extern menu ShopMenu;
