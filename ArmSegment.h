//
// Created by Melvin Stans on 15/09/2018.
//

#ifndef ROBOTARM_ARMSEGMENT_H
#define ROBOTARM_ARMSEGMENT_H

#include "Eigen/Core"
#include <SFML/Graphics/RenderWindow.hpp>
using Eigen::Vector3d;

class ArmSegment {
public:
    double length;
    double angle;
    double cosAngle;
    double sinAngle;
    Vector3d beginPoint;
    Vector3d endPoint;
    void draw(sf::RenderWindow *window);
    void calculateEndPoint(Vector3d beginPoint, double angle);
    void calculateBeginPoint(Vector3d endPoint, double angle);
//    void calculateEndPointChild(Vector3d beginPoint,ArmSegment child, double length, double angle);
    void move(Vector3d newBeginPoint);
    ArmSegment(Vector3d, double ,double);
    ArmSegment();
};

#endif //ROBOTARM_ARMSEGMENT_H
