#include "Theme.h"
#include <iostream>
#include <string>
#include <vector>
#include "SaveLoad.h"
#include "include/json.hpp"

std::string themesFile = "SaveData/Themes.json";

namespace Themes 
{
    std::vector<Theme> ExternThemes;

    void loadExternThemes()
    {
        loadFromFile(themesFile, ExternThemes);
    }
}