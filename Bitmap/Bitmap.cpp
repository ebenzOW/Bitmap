#include <iostream>
#include <deque>
#include <string>
#include "bmp.hpp"

using namespace std;
int const MAX_SIZE = 1000;
bool visited[MAX_SIZE][MAX_SIZE] = { false };

struct pixel {
    int x;
    int y;
    pixel(int x_ = 0, int y_ = 0 ) : x{ x_ }, y{ y_ } {}
};



void floodFill(BMP &image, int startX, int startY, color fillColor)
{
    int h = image.get_height();
    int w = image.get_width();
    if (startX < 0 || startX >= w || startY <0 || startY >= h)
        return;

    color startColor = image.get_pixel(startX, startY); //Getting the original color of the space
    if (startColor.r == fillColor.r && startColor.b == fillColor.b
        && startColor.g == fillColor.g) return;

    visited[startX][startY] = true;

    deque<pixel> fillDeque;
    fillDeque.push_back(pixel(startX, startY));

    while (!fillDeque.empty())
    {
        cout << "looping \n";
        pixel temp = fillDeque.front();
        fillDeque.pop_front();
        color tempColor = image.get_pixel(temp.x, temp.y);
        if (tempColor.r == startColor.r && tempColor.b == startColor.b
            && tempColor.g == startColor.g) 
        {
            image.set_pixel(temp.x, temp.y, fillColor);
            for (int x = temp.x - 1; x <= temp.x + 1; x++) //find the neighbors
            {
                for (int y = temp.y - 1; y <= temp.y + 1; y++)
                {
                    if (x == temp.x && y == temp.y) continue;
                    if ((x >= 0 && x < w && y >= 0 && y < h) && (visited[x][y] == false))
                    {
                        fillDeque.push_back(pixel(x, y));
                        visited[x][y] = true;
                    }
                }
            }
        }
       
    }
}
BMP applySquareBlur(BMP image, int blur_size, string file_name)
{
   
    BMP temp = BMP(file_name);
    int halfSize = blur_size/2;
    int nx = 0;
    int ny = 0;
   for(int x = 0; x < 1000; x++)
   {
        for(int y = 0; y < 1000; y++)
        {
        int totalR, totalG, totalB, count = 0;
        for(int dy = -halfSize; dy <= halfSize; dy++)
            for(int dx = -halfSize; dx <= halfSize; dx++)
            {
                nx = x + dx;
                ny = y + dy;
                if(nx >= 0 && nx < MAX_SIZE && ny >=0 )
            }
        }
    }
}

int main()
{
    BMP image("sample2.bmp");
    color fill(255, 0, 0);
    floodFill(image, 300, 300, fill);
    image.write("C:\\Users\\erics\\Documents\\GitHub\\Bitmap\\Bitmap\\image2.bmp");
  
}

