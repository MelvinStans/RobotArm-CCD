#include <iostream>
#include <SFML/Graphics.hpp>
#include "Arm.h"

#define WIDTH 400
#define HEIGHT 400

int main() {
    Arm arm(50, 3);

    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "RobotArm");
    Vector2d mousePos;

    while (window.isOpen()) {
        // clear the window with black color
        window.clear(sf::Color::Black);

        // check all the window's events that were triggered
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        mousePos = Vector2d(sf::Mouse::getPosition(window).x, HEIGHT - sf::Mouse::getPosition(window).y);
                        arm.moveToPoint(mousePos);
                    }
                    break;

                default:
                    break;
            }

        }

        // Draw the arm
        for (int i = 0; i < arm.segmentCount; ++i) {
            arm.armSegments[i].draw(&window);
        }

        // End the current frame and display
        window.display();
    }
    exit(0);
}

