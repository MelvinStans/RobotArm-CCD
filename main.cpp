#include <iostream>
#include <SFML/Graphics.hpp>
#include "Arm.h"

#define WIDTH 400
#define HEIGHT 400

int main() {
    int slength[] = {50,50,50};
    Arm arm(slength, 3);
    arm.generateArm();

    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "RobotArm");

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < arm.segmentCount; ++i) {
            arm.armSegments[i].draw(&window);
        }

        // end the current frame
        window.display();
    }

    return 0;
}

