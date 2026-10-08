#include <SFML/Graphics.hpp>

struct{
    int originIndex;
    sf::Color color;

} Pixel;

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Title");

    sf::Image image("b.jpg");

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