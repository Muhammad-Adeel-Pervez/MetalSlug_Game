#include <SFML/Graphics.hpp>

int main()
{
    // 1. Ek window banayein (800 wide, 600 high)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Metal Slug - SFML Test!");

    // 2. Ek circle banayein (radius 100)
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green); // Circle ka color green rakha hai
    shape.setPosition(300, 200);          // Window mein circle ki jagah set ki

    // 3. Game Loop (Ye tab tak chalta rahega jab tak window band na ho)
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Agar "X" button dabayein toh window band ho jaye
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 4. Rendering (Drawing ka kaam)
        window.clear();          // Purani screen saaf karo
        window.draw(shape);      // Circle draw karo
        window.display();        // Sab kuch screen par dikhao
    }

    return 0;
}