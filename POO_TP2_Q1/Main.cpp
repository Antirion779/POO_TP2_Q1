#include <SFML/Graphics.hpp>

//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}

#include "Simulation.h"

int main() {
    Simulation simulation;
    simulation.run();
    return 0;
}
