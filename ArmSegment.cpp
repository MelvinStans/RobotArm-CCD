//
// Created by Melvin Stans on 15/09/2018.
//

#include "ArmSegment.h"
#include <cmath>

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

ArmSegment::ArmSegment(Vector2d bp, double length, double angle) {
    this->beginPoint = bp;
    this->length = length;
    calculateEndPoint(bp, length, angle);
    this->angle = angle;
}

void ArmSegment::calculateEndPoint(Vector2d bp, double length, double angle) {
    double y = (length * cos(angle)) + bp.y();
    double x = (length * sin(angle)) + bp.x();
    this->endPoint = Vector2d(x,y);
    this->angle = angle;
}


