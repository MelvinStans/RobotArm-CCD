//
// Created by Melvin Stans on 15/09/2018.
//

#include <iostream>
#include "ArmSegment.h"
#include "Arm.h"

void Arm::generateArm() {
    std::cout << "Generating arm with " << segmentCount << " segments" << std::endl;

    // Make first segment
    armSegments[0].beginPoint = Vector2d(200,0);
    armSegments[0].endPoint = Vector2d(200,50);

    // Make remaing segments
    int total = 0;
    for (int j = 1; j < segmentCount; ++j) {
        total = total + segmentLengths[j];
        armSegments[j] = ArmSegment(Vector2d(200,total),Vector2d(200,segmentLengths[j]+total));
    }
}

Arm::Arm() = default;

Arm::Arm(int a[], int c) {
    for (int i = 0; i < c ; ++i) {
        segmentLengths[i] = a[i];
        armSegments[i] = ArmSegment();
    }
    segmentCount = c;
}

