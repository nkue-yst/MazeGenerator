#pragma once
#include <string>
#include <vector>

namespace maze
{
    using vInt = std::vector<int>;
    using vvInt = std::vector<vInt>;

    const int ROAD = 0;
    const int WALL = 1;
    const std::string errMsg = "Width and Height must be 5 or more.";
}