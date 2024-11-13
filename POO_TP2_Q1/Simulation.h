#ifndef SIMULATION_H
#define SIMULATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <mutex>
#include "Pigeon.h"
#include "Food.h"

class Simulation {
public:
    Simulation();
    void run();

private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<Pigeon>> pigeons;
    std::vector<Food> food;
    std::mutex foodMutex;

    float lastScareTime;
    sf::CircleShape scareCircle;
    bool scareActive;
    std::atomic<bool> running;  // Global running flag

    void addFood(float x, float y);
    void drawScene();
    void triggerScare();
};

#endif // SIMULATION_H
