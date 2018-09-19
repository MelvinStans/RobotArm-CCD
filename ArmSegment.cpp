//
// Created by Melvin Stans on 15/09/2018.
//

#include "ArmSegment.h"

void ArmSegment::draw(sf::RenderWindow *window){
    sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f(this->beginPoint.x(), window->getSize().y - this->beginPoint.y()), sf::Color::Green),
                    sf::Vertex(sf::Vector2f(this->endPoint.x(), window->getSize().y - this->endPoint.y()), sf::Color::Red)
            };
    window->draw(line, 2, sf::Lines);
}

ArmSegment::ArmSegment() {
    this->beginPoint = Vector2d(0,0);
    this->endPoint = Vector2d(0,0);
}

ArmSegment::ArmSegment(Vector2d bp, Vector2d ep) {
    this->beginPoint = bp;
    this->endPoint = ep;
}


