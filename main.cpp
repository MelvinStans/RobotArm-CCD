#include <iostream>
#include "Arm.h"

int main() {
    Arm newArm;
    newArm.segmentCount = 3;
    float segLengths[] = {1.0,2.0,3.0};
    newArm.generateArm(segLengths,newArm.segmentCount);

    return 0;
}

