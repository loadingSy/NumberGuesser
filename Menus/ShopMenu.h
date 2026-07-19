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
        : name(cName), price([cPrice](){return cPrice;}), apply(cApply) {}
        shopItem(std::string cName, std::function<float()> cPrice, std::function<purchaseInfo()> cApply)
        : name(cName), price(cPrice), apply(cApply) {}
        
        float getPrice()
        {
            return price();
        }

        void setPrice(float p) {price = [p](){return p;};}
        void setPrice(std::function<float()> p) {price = p;}

        std::string name = "";
        int index;
        bool available = true;
        purchaseInfo purchase()
        {
            float curPrice = getPrice();
            
            if(tempRunningSaveData.points >= curPrice)
            {
                purchaseInfo appliedData = apply();
                if(appliedData.accepted)
                {
                    tempRunningSaveData.points -= curPrice;
                    return appliedData;
                }
                return {false, std::nullopt};
            }
            return {false, "Not enough Points"};
        }
    private:
        std::function<purchaseInfo()> apply;
        std::function<float()> price;

};



extern menu ShopMenu;
