#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <SFML/Graphics.hpp>
using namespace std;

struct Pixel{
    int originIndex;
    sf::Color color;

    bool operator<(const Pixel &a) const
    {
        return originIndex < a.originIndex;
    }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Title");

    sf::Image image("b.jpg");

    sf::Vector2 dim(image.getSize());

    int width = dim.x, height = dim.y;
    
    long int imgPixelCount = (long) width * height;

    //cout << "Width: " << width << " , "<< "Height: " << height << endl << "Pixel Count: " << imgPixelCount << endl;
    
    vector<Pixel> pixels(imgPixelCount);

    // filling List

    int index;
    sf::Color c;

    for(unsigned int y = 0; y < height; y++)
    {
        for(unsigned int x = 0; x < width; x++)
        {
            index = y * width + x;
            c = image.getPixel({x, y});
            pixels[index] = {index , c};
        }
    }

    // shuffling array
    random_device rd;    
    mt19937 rng(rd());                      

    shuffle(pixels.begin(), pixels.end(), rng);

    // writing shuffled array to image

    for(int i = 0; i < imgPixelCount; i++)
    {
        unsigned int x = i % width;
        unsigned int y = i / width;

        image.setPixel({x,y} , pixels[i].color);

    }


    sf::Texture texture(image);

    sf::Sprite sprite(texture);



    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color(64, 64, 64));

        // draw
        window.draw(sprite);



        window.display();
    }

    return 0;
}