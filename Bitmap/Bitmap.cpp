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
                        color neighborColor = image.get_pixel(x, y);
                        if(neighborColor.r == startColor.r && neighborColor.g == startColor.g && neighborColor.b == startColor.b){
                        fillDeque.push_back(pixel(x, y));
                        visited[x][y] = true;
                        }
                    }
                }
            }
        }
       
    }
}
void applySquareBlur(BMP &image, int blur_size, string file_name)
{
   
    BMP source = image;
    int halfSize = blur_size/2;
    int nx = 0;
    int ny = 0;
   for(int x = 0; x < image.get_width(); x++)
   {
        for(int y = 0; y < image.get_height(); y++)
        {
        int totalR= 0; 
        int totalG= 0;
        int totalB= 0; 
        int count = 0;
        for(int dy = -halfSize; dy <= halfSize; dy++)
            for(int dx = -halfSize; dx <= halfSize; dx++)
            {
                nx = x + dx;
                ny = y + dy;
                if(nx >= 0 && nx < MAX_SIZE && ny >=0  && ny < MAX_SIZE)
                {
                    color neighborColor = source.get_pixel(nx, ny);
                    totalR += neighborColor.r;
                    totalG += neighborColor.g;
                    totalB += neighborColor.b;
                    count += 1;
                }
            }
            if(count > 0) {
                color averageColor = color(totalR / count, totalG / count, totalB / count);
                image.set_pixel(x, y, averageColor);
            }
        }
    }
    image.write(file_name + ".bmp");
}

int main()
{
    BMP image("sample2.bmp");
    color fill(255, 0, 0);
    floodFill(image, 300, 300, fill);
    BMP blurredImage("sample.bmp");
    applySquareBlur(blurredImage, 20, "samplecopy");

    image.write("image2.bmp");
  
}

