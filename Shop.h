#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include "SaveLoad.h"
using namespace std;


extern unordered_map<string, function<bool()>> shopItemsFunction;

void intializeShop(saveData& saveDataPointer);

void openShop(int& points);
