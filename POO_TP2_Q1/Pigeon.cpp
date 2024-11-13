#include "Pigeon.h"
#include <chrono>
#include <random>
#include <cmath>
#include <iostream>

Pigeon::Pigeon(float x, float y, std::vector<Food>& foodList, std::mutex& foodMutex, float speed, std::atomic<bool>& runningFlag)
    : asleep(true), running(true), speed(speed), scared(false), scareDuration(0), foodList(foodList), foodMutex(foodMutex), globalRunningFlag(runningFlag) {
    shape.setRadius(10.f);
    shape.setPosition(x, y);
    updateColor();
}

Pigeon::~Pigeon() {
    stop();
}

void Pigeon::start() {
    try {
        thread = std::thread(&Pigeon::behavior, this);
    }
    catch (const std::exception& e) {
        std::cerr << "Exception starting thread: " << e.what() << std::endl;
    }
}

void Pigeon::stop() {
    running = false;
    try {
        if (thread.joinable()) {
            thread.join();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception stopping thread: " << e.what() << std::endl;
    }
}

void Pigeon::setAsleep(bool state) {
    if (!scared) {
        asleep = state;
        updateColor();
    }
}

void Pigeon::updateColor() {
    try {
        if (scared) {
            shape.setFillColor(sf::Color::Yellow);  // Yellow for scared
        }
        else if (asleep) {
            shape.setFillColor(sf::Color(138, 43, 226));  // Purple for asleep
        }
        else {
            shape.setFillColor(sf::Color::Blue);  // Blue for moving
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in updateColor: " << e.what() << std::endl;
    }
}

void Pigeon::scare(const sf::Vector2f& scareSource) {
    try {
        scared = true;
        scareDuration = 5.0f;
        float dx = shape.getPosition().x - scareSource.x;
        float dy = shape.getPosition().y - scareSource.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        // Avoid divide-by-zero errors by ensuring distance is not zero
        if (distance > 0) {
            fleeDirection = sf::Vector2f(dx / distance, dy / distance);
        }
        else {
            fleeDirection = sf::Vector2f(1.0f, 0.0f);  // Default direction if distance is zero
        }

        updateColor();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in scare: " << e.what() << std::endl;
    }
}

void Pigeon::flee() {
    try {
        shape.move(fleeDirection * speed * 2.0f);
        scareDuration -= 0.1f;

        if (scareDuration <= 0) {
            scared = false;
            updateColor();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in flee: " << e.what() << std::endl;
    }
}

Food* Pigeon::findFreshestFood() {
    Food* closestFood = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    const float visionRadius = 700.0f;  // Define vision radius for pigeons

    try {
        std::lock_guard<std::mutex> lock(foodMutex);  // Ensure thread safety for accessing food list

        for (auto& f : foodList) {
            try {
                if (!f.fresh) continue;  // Ignore stale food

                // Calculate the distance between the pigeon and the food
                float dx = f.shape.getPosition().x - shape.getPosition().x;
                float dy = f.shape.getPosition().y - shape.getPosition().y;

                // Exception handling for unexpected zero values or outliers
                if (std::isnan(dx) || std::isnan(dy)) {
                    std::cerr << "Warning: NaN detected in food coordinates.\n";
                    continue;
                }

                float distance = std::sqrt(dx * dx + dy * dy);

                // Additional check to avoid errors with distance calculation
                if (std::isnan(distance) || distance < 0.0f) {
                    std::cerr << "Warning: Invalid distance calculated.\n";
                    continue;
                }

                // Only consider food within the vision radius
                if (distance < minDistance && distance <= visionRadius) {
                    minDistance = distance;
                    closestFood = &f;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Exception in food distance calculation: " << e.what() << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in findFreshestFood while accessing food list: " << e.what() << std::endl;
    }

    return closestFood;
}

void Pigeon::moveToFood(Food* food) {
    if (!food) return;

    try {
        float dx = food->shape.getPosition().x - shape.getPosition().x;
        float dy = food->shape.getPosition().y - shape.getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < 5.0f) {
            std::lock_guard<std::mutex> lock(foodMutex);
            auto it = std::find_if(foodList.begin(), foodList.end(), [food](const Food& f) { return &f == food; });
            if (it != foodList.end()) {
                foodList.erase(it);
            }
        }
        else {
            shape.move(speed * dx / distance, speed * dy / distance);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in moveToFood: " << e.what() << std::endl;
    }
}

void Pigeon::behavior() {
    try {
        while (running && globalRunningFlag) {  // Check both local and global running flags
            if (scared) {
                flee();
            }
            else if (asleep) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            else {
                Food* targetFood = findFreshestFood();
                if (targetFood) {
                    moveToFood(targetFood);
                }
                else {
                    setAsleep(true);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in behavior: " << e.what() << std::endl;
    }
}

bool Pigeon::isTooCloseTo(const Pigeon& other) const {
    try {
        float dx = other.shape.getPosition().x - shape.getPosition().x;
        float dy = other.shape.getPosition().y - shape.getPosition().y;
        return std::sqrt(dx * dx + dy * dy) < 20.0f;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in isTooCloseTo: " << e.what() << std::endl;
        return false;
    }
}
