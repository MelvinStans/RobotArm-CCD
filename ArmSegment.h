//
// Created by Melvin Stans on 15/09/2018.
//

#ifndef ROBOTARM_ARMSEGMENT_H
#define ROBOTARM_ARMSEGMENT_H

#include "Eigen/Core"
#include <SFML/Graphics/RenderWindow.hpp>
using Eigen::Vector2d;

class ArmSegment {
public:
//    int length;
    Vector2d beginPoint;
    Vector2d endPoint;
    void draw(sf::RenderWindow *window);
    ArmSegment();
    ArmSegment(Vector2d, Vector2d);
};

#endif //ROBOTARM_ARMSEGMENT_H
