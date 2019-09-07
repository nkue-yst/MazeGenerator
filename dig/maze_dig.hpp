#pragma once
#include "../maze_gen.hpp"
#include <ctime>
#include <iostream>

namespace maze
{
    namespace dig
    {
        struct vec2
        {
            int x;
            int y;
        } dir[] = {
            {0, -1},
            {1, 0},
            {0, 1},
            {-1, 0},
        };

        /* Initialize maze data */
        int initMap(vvInt& map, int& width, int& height)
        {
            if (width < 5 || height < 5)
            {
                std::cout << errMsg << std::endl << std::endl;
                return 1;
            }
            if (width % 2 == 0) width++;
            if (height % 2 == 0) height++;

            map.assign(width, vInt(height, WALL));

            return 0;
        }

        /* Create random number.(Odd number) */
        int randomOdd(int mod)
        {
            srand((unsigned int)time(NULL));

            int r = 1 + rand() % mod;

            if (r % 2 == 0) r++;
            if (r > mod) r -= 2;

            return r;
        }

        /* Create maze */
        void digMaze(vvInt& map, const int x, const int y)
        {
            int d = rand() % 4;
            int dd = d;

            while (1)
            {
                size_t dx = x + dir[d].x * 2;
                size_t dy = y + dir[d].y * 2;

                if (dx < 0 || map.size() <= dx || dy < 0 || map[0].size() <= dy || map[dx][dy] != WALL)
                {
                    d++;

                    if (d == 4) d = 0;
                    if (d == dd) return;
                    continue;
                }
                map[dx][dy] = ROAD;
                map[x + dir[d].x][y + dir[d].y] = ROAD;

                digMaze(map, dx, dy);
                d = dd = rand() % 4;
            }
        }

        /* Start create maze */
        int createMaze(vvInt& map, int& width, int& height)
        {
            if (initMap(map, width, height)) return 1;

            int x = randomOdd(width - 2);
            int y = randomOdd(height - 2);

            digMaze(map, x, y);

            return 0;
        }

        /* Output map on console */
        void printMap(const vvInt map)
        {
            for (size_t y = 0; y < map[0].size(); y++)
            {
                for (size_t x = 0; x < map.size(); x++)
                {
                    std::cout << ((map[x][y] == WALL) ? "¡" : "@");
                }
                std::cout << std::endl;
            }
        }
    }
}