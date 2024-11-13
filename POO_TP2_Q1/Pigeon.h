#ifndef PIGEON_H
#define PIGEON_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <mutex>
#include "Food.h"

class Pigeon {
public:
    sf::CircleShape shape;
    std::atomic<bool> asleep;

    Pigeon(float x, float y, std::vector<Food>& foodList, std::mutex& foodMutex, float speed, std::atomic<bool>& runningFlag);
    ~Pigeon();
    void start();
    void stop();
    void setAsleep(bool state);
    void scare(const sf::Vector2f& scareSource);
    bool isTooCloseTo(const Pigeon& other) const;

    Pigeon(const Pigeon&) = delete;
    Pigeon& operator=(const Pigeon&) = delete;

private:
    std::thread thread;
    std::atomic<bool> running;
    float speed;
    bool scared;
    float scareDuration;
    sf::Vector2f fleeDirection;
    std::vector<Food>& foodList;
    std::mutex& foodMutex;
    std::atomic<bool>& globalRunningFlag;  // Reference to global running flag

    void behavior();
    void updateColor();
    Food* findFreshestFood();
    void moveToFood(Food* food);
    void flee();
};

#endif // PIGEON_H
