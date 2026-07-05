#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <random>

using namespace std;

void returnError(string errorMessage);

int randomInRange(int min, int max)
{
    random_device dev;
    mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max);
    return dist6(rng);
}

int validateToString(string stringToCheck)
{
    try
    {
        int processedInput =  stoi(stringToCheck);
        return processedInput;
    }
    catch (invalid_argument& reason) {
        returnError(reason.what());
        return -1;
    }
    catch (out_of_range& reason)
    {
        returnError(reason.what());
        return -1;
    }
}

void returnError(string errorMessage)
{
    cout << "Error happened: " << errorMessage << "\n";
}