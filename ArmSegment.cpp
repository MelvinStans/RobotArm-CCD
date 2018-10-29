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
    this->beginPoint = Vector3d(0,0,0);
    this->endPoint = Vector3d(0,0,0);
    this->angle=0;
    this->length = 0;
}

ArmSegment::ArmSegment(Vector3d bp, double length, double angle) {
    this->beginPoint = bp;
    this->length = length;
    this->angle = angle;
    this->cosAngle = cos(angle);
    this->sinAngle = sin(angle);
    calculateEndPoint(bp, angle);
}

void ArmSegment::calculateEndPoint(Vector3d bp, double angle) {
    double y = (this->length * cos(angle)) + bp.y();
    double x = (this->length * sin(angle)) + bp.x();
    double z = 0;
    this->endPoint = Vector3d(x,y,z);
}

void ArmSegment::calculateBeginPoint(Vector3d endPoint, double angle) {
    double y = (this->length * tan(angle)) + endPoint.y();
    double x = (this->length * cos(angle)) + endPoint.x();
    double z = 0;
    this->beginPoint = Vector3d(x,y,z);
}

void ArmSegment::move(Vector3d newPoint){
    // calc delta newpoint and current point
    Vector3d delta;
    delta.x() = this->beginPoint.x() - newPoint.x();
    delta.y() = this->beginPoint.y() - newPoint.y();
    delta.z() = this->beginPoint.z() - newPoint.z();


    this->beginPoint = newPoint;
    this->endPoint = this->endPoint + delta;
}

