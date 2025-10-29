#include <iostream>
#include <deque>

#include "bmp.hpp"

using namespace std;
int const MAX_SIZE = 1000;
bool visited[MAX_SIZE][MAX_SIZE] = { false };

struct pixel {
    int x;
    int y;
    pixel(int x_ = 0, int y_ = 0 ) : x{ x_ }, y{ y_ } {}
};

void floodFill(BMP image, int startX, int startY, color fillColor)
{
    int h = image.get_height();
    int w = image.get_width();
    if (startX < 0 || startX > w || startY <0 || startY > h)
        return;

    color startColor = image.get_pixel(startX, startY); //Getting the original color of the space
    if (startColor.r == fillColor.r && startColor.b == fillColor.b
        && startColor.g == fillColor.g) return;

    visited[startX][startY] = true;

    deque<pixel> fillDeque;
    fillDeque.push_back(pixel(startX, startY));

    while (!fillDeque.empty())
    {
        pixel temp = fillDeque.front();
        fillDeque.pop_front();
        color tempColor = image.get_pixel(temp.x, temp.y);
        if (tempColor.r == startColor.r && tempColor.b == startColor.b
            && tempColor.g == startColor.g) 
        {
            image.set_pixel(temp.x, temp.y, fillColor);
            for(int x = x-1; x<=x+1; x++)
                for (int y = y - 1; y <= y + 1; y++)
                {
                    if ((x < 0 || x > w || y <0 || y > h) && visi)
                }
        }
       
    }
}

int main()
{

    BMP image("sample2.bmp");
    image.write("img1.bmp");
  
}

