#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

class Food {
public:
    sf::CircleShape shape;
    bool fresh;

    Food(float x, float y);
    void setStale();
    void updateStaleStatus();

private:
    std::chrono::steady_clock::time_point creationTime;
};
