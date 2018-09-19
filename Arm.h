//
// Created by Melvin Stans on 15/09/2018.
//

#ifndef ROBOTARM_ARM_H
#define ROBOTARM_ARM_H

#include "ArmSegment.h"
class Arm {
public:
    int segmentLengths[5];
    int segmentCount;
    ArmSegment armSegments[5];
    void generateArm();
    Arm(int[], int);
    Arm();
};

#endif //ROBOTARM_ARM_H
