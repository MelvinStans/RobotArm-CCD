//
// Created by Melvin Stans on 15/09/2018.
//

#include <iostream>
#include "ArmSegment.h"
#include "Arm.h"


void Arm::generateArm(float segmentLengths[],int segmentCount) {
    std::cout << "Generating arm with " << segmentCount << " segments" << std::endl;

    ArmSegment armSegments [segmentCount];

    float totalLength = 0;
    for (int i = 0; i < segmentCount; ++i) {
        armSegments[i].beginPoint = Vector3d(0,totalLength,0);
        armSegments[i].length = segmentLengths[i];
        totalLength = totalLength + segmentLengths[i];
        armSegments[i].endPoint = Vector3d(0,totalLength,0);

        std::cout << "segment " << i << " with begin pos " << armSegments[i].beginPoint
            << " with end pos " << armSegments[i].endPoint
            << " with length " << armSegments[i].length << std::endl;
    }

}

