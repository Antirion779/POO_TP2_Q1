#include "Simulation.h"
#include <random>
#include <chrono>
#include <exception>
#include <iostream>

Simulation::Simulation() : window(sf::VideoMode(1920, 1080), "Pigeon Simulation"), lastScareTime(0), scareActive(false), running(true) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distX(0, 1920);
    std::uniform_real_distribution<> distY(0, 1080);
    std::uniform_real_distribution<> speedDist(2.0f, 4.0f);

    for (int i = 0; i < 100; ++i) {
        float x = static_cast<float>(distX(gen));
        float y = static_cast<float>(distY(gen));
        float speed = speedDist(gen);
        pigeons.push_back(std::make_unique<Pigeon>(x, y, food, foodMutex, speed, running));
    }

    for (auto& pigeon : pigeons) {
        pigeon->start();
    }

    scareCircle.setRadius(200.0f);
    scareCircle.setOutlineColor(sf::Color(255, 255, 0, 128));
    scareCircle.setOutlineThickness(2.0f);
    scareCircle.setFillColor(sf::Color::Transparent);
    scareCircle.setOrigin(scareCircle.getRadius(), scareCircle.getRadius());
}

void Simulation::addFood(float x, float y) {
    try {
        std::lock_guard<std::mutex> lock(foodMutex);
        food.emplace_back(x, y);
        for (auto& pigeon : pigeons) {
            pigeon->setAsleep(false);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in addFood: " << e.what() << std::endl;
    }
}

void Simulation::triggerScare() {
    try {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distX(0, 1920);
        std::uniform_real_distribution<> distY(0, 1080);
        sf::Vector2f scareSource(distX(gen), distY(gen));

        float scareRadius = 200.0f;
        scareActive = true;
        scareCircle.setPosition(scareSource);

        // Only scare pigeons within the updated scare radius
        for (auto& pigeon : pigeons) {
            float dx = pigeon->shape.getPosition().x - scareSource.x;
            float dy = pigeon->shape.getPosition().y - scareSource.y;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance <= scareRadius) {
                pigeon->scare(scareSource);
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Exception in triggerScare: " << e.what() << std::endl;
    }
}

void Simulation::drawScene() {
    try {
        window.clear();
        for (auto& pigeon : pigeons) {
            window.draw(pigeon->shape);
        }
        for (auto& f : food) {
            window.draw(f.shape);
        }

        if (scareActive) {
            window.draw(scareCircle);
        }

        window.display();

    }
    catch (const std::exception& e) {
        std::cerr << "Exception in drawScene: " << e.what() << std::endl;
    }
}

void Simulation::run() {
    auto startTime = std::chrono::steady_clock::now();
    try {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    running = false;  // Signal pigeons to stop
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    addFood(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                }
            }

            // Update each food's stale status
            for (auto& f : food) {
                f.updateStaleStatus();
            }

            auto currentTime = std::chrono::steady_clock::now();
            float elapsedTime = std::chrono::duration<float>(currentTime - startTime).count();
            if (elapsedTime - lastScareTime >= 10.0f) {
                triggerScare();
                lastScareTime = elapsedTime;
            }

            if (scareActive && elapsedTime - lastScareTime >= 5.0f) {
                scareActive = false;
            }

            drawScene();
        }

        for (auto& pigeon : pigeons) {
            pigeon->stop();  // Ensure each pigeon stops
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Exception in run loop: " << e.what() << std::endl;
    }
}