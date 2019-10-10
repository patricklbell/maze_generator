#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iterator>
#include <array>
#include "bitmap_image.hpp"
#define cellW 100
#define cellH 100
#define W cellW * 2 + 1
#define H cellH * 2 + 1
#define SIZE 1

using vec2=std::array<int, 2>;

inline constexpr std::array<vec2, 4> getNeighbours(int x, int y){
    return {{{x, y+1},{x, y-1},{x+1, y},{x+1, y}}};
}

int main()
{
    bool cells[W][H] = {{false}};
    std::vector<vec2> wallList;
    std::array<vec2, 4> neighbours;

    // pick a cell to start, in this case the bottom left, add neighbours
    cells[1][1] = true;
    neighbours = std::move(getNeighbours(1, 1)); // look it &&
    wallList.insert(wallList.end(), neighbours.cbegin(), neighbours.cend());

    // int choosen[2] = {rand() % W + 1, rand() % H + 1};
    // cells[choosen[0]*2][choosen[1]*2] = true;

    while (wallList.size() != 0) {
        // choose random wall from list
        int pos = std::rand() % wallList.size();
        int x = wallList[pos][0];
        int y = wallList[pos][1];

        // test if edge, if so remove wall from list
        if (!(x == 0 || x == W - 1 || y == 0 || y == H - 1)){
            // find cells the wall divides, note double cells
            if(x % 2 == 0){
                if(cells[x-1][y] != cells[x+1][y]) {
                    cells[x][y] = true;
                    cells[x-1][y] = true;
                    cells[x+1][y] = true;

                    neighbours = getNeighbours(x-1, y);
                    wallList.insert(wallList.end(), std::begin(neighbours), std::end(neighbours));
                    neighbours = getNeighbours(x+1, y);
                    wallList.insert(wallList.end(), std::begin(neighbours), std::end(neighbours));
                }
            } else {
                if(cells[x][y-1] != cells[x][y+1]) {
                    cells[x][y] = true;
                    cells[x][y-1] = true;
                    cells[x][y+1] = true;

                    neighbours = getNeighbours(x, y-1);
                    wallList.insert(wallList.end(), std::begin(neighbours), std::end(neighbours));
                    neighbours = getNeighbours(x, y+1);
                    wallList.insert(wallList.end(), std::begin(neighbours), std::end(neighbours));
                }
            }
        }
        wallList.erase(wallList.begin() + pos);
    }

    //render walls
    bitmap_image image(W * SIZE, H * SIZE);
    //image.set_all_channels(255, 255, 255);
    image.clear();

    //image_drawer draw(image);

    //draw.pen_width(SIZE);
    //draw.pen_color(0, 0, 0);
    for (int x = 0; x < W; x++){
        for (int y = 0; y < H; y++){
            if(cells[x][y]){
                //std::cout << "at pos: " << x << ", " << y << std::endl;
                image.set_pixel(x, y, make_colour(255, 255, 255));  
            }
        }
    }
    
    image.save_image("maze.bmp");
    return 0;
}