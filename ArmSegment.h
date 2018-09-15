//
// Created by Melvin Stans on 15/09/2018.
//

#ifndef ROBOTARM_ARMSEGMENT_H
#define ROBOTARM_ARMSEGMENT_H

#include "Eigen/Core"
using Eigen::Vector3d;

class ArmSegment {
public:
    float length;
    Vector3d beginPoint;
    Vector3d endPoint;
};

#endif //ROBOTARM_ARMSEGMENT_H
