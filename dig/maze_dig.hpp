/**
 * @file maze_dig.hpp
 * @brief 穴掘り法による迷路生成
 * @author Yoshito Nakaue
 * @date 2019/09/07
 */

#pragma once
#include "../Base/base.hpp"
#include <ctime>
#include <iostream>

namespace maze
{
    namespace dig
    {
        //! 2次元ベクトル
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

        /**
         * @fn int initMap(vvInt& map, int& width, int& height)
         * @brief マップ内全てを壁で初期化する
         * @param map 生成する迷路を格納するマップ
         * @param width マップの横幅
         * @param height マップの高さ
         * @return 成功したら0, 失敗したら1を返す
         */
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

        /**
         * @fn int randomOdd(int mod)
         * @brief ランダムな奇数を生成
         * @param mod 乱数の最大値
         * @return ランダムな奇数を生成
         */
        int randomOdd(int mod)
        {
            srand((unsigned int)time(NULL));

            int r = 1 + rand() % mod;

            if (r % 2 == 0) r++;
            if (r > mod) r -= 2;

            return r;
        }

        /**
         * @fn void digMaze(vvInt& map, const int x, const int y)
         * @brief 穴掘り法を実行する
         * @param map 生成した迷路を格納するマップ
         * @param x マップの横幅
         * @param y マップの高さ
         */
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

        /**
         * @fn int createMaze(vvInt& map, int& width, int& height)
         * @brief 迷路を生成する
         * @param map 生成した迷路を格納するマップ
         * @param width 生成するマップの横幅
         * @param height 生成するマップの高さ
         * @return 成功したら0, 失敗したら1
         */
        int createMaze(vvInt& map, int& width, int& height)
        {
            if (initMap(map, width, height)) return 1;

            int x = randomOdd(width - 2);
            int y = randomOdd(height - 2);

            digMaze(map, x, y);

            return 0;
        }

        /**
         * @fn void printMap(const vvInt map)
         * @brief マップを出力する
         * @param map 出力するマップ
         */
        void printMap(const vvInt map)
        {
            for (size_t y = 0; y < map[0].size(); y++)
            {
                for (size_t x = 0; x < map.size(); x++)
                {
                    std::cout << ((map[x][y] == WALL) ? "* " : "  ");
                }
                std::cout << std::endl;
            }
        }
    }
}