#include "Food.h"
#include <iostream>

Food::Food(float x, float y) : fresh(true) {
    try {
        shape.setRadius(5.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);
        creationTime = std::chrono::steady_clock::now();
        std::cout << "Food created at position (" << x << ", " << y << ") and is fresh.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in Food constructor: " << e.what() << std::endl;
    }
}

void Food::setStale() {
    try {
        fresh = false;
        shape.setFillColor(sf::Color::White);  // Change color to indicate stale food
        std::cout << "Food at position (" << shape.getPosition().x << ", " << shape.getPosition().y << ") has turned stale.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in setStale: " << e.what() << std::endl;
    }
}

void Food::updateStaleStatus() {
    try {
        auto now = std::chrono::steady_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - creationTime).count();

        if (fresh && elapsedSeconds >= 5) {
            setStale();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in updateStaleStatus: " << e.what() << std::endl;
    }
}
