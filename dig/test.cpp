#include "maze_dig.hpp"

int main()
{
    int width, height;
    maze::dig::vvInt map;

    while (1)
    {
        while (1)
        {
            std::cout << "Width << ";
            std::cin >> width;
            std::cout << "Height << ";
            std::cin >> height;

            if (maze::dig::createMaze(map, width, height) == 0) break;
        }
        maze::dig::printMap(map);
        std::cout << std::endl;
    }
}