//
// Created by Melvin Stans on 15/09/2018.
//

#include <iostream>
#include "ArmSegment.h"
#include "Arm.h"

void Arm::generateArm() {
    std::cout << "Generating arm with " << segmentCount << " segments" << std::endl;

    // Make first segment
    armSegments[0] = ArmSegment(Vector2d(200,0),50,0);

    // Make remaing segments
    int total = 0;
    for (int j = 1; j < segmentCount; ++j) {
        total = total + segmentLengths[j];
        armSegments[j] = ArmSegment(Vector2d(200,total),segmentLengths[j],0);
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

void Arm::updateArm(Vector2d targetPoint) {
    // offset axis with beginpoint
    Vector2d off = armSegments[1].beginPoint;
    targetPoint = targetPoint-off;
    armSegments[1].endPoint = armSegments[1].endPoint-off;
    armSegments[1].beginPoint = armSegments[1].beginPoint-off;

    double dot = (armSegments[1].endPoint.x() * targetPoint.x()) + (armSegments[1].endPoint.y() * targetPoint.y());

    double targetLength= sqrt(((targetPoint.x())*(targetPoint.x()))+(targetPoint.y()*targetPoint.y()));

    double newAngleCos = (dot / (armSegments[1].length * targetLength));
    double newAngle = acos(newAngleCos);

    newAngle = armSegments[1].angle - newAngle;

    // reset offset
    armSegments[1].endPoint = armSegments[1].endPoint+off;
    armSegments[1].beginPoint = armSegments[1].beginPoint+off;
    if (newAngleCos <0.99) {
        armSegments[1].calculateEndPoint(armSegments[0].endPoint,armSegments[1].length,newAngle);
    }

    double sin2 = sin(newAngle);
    double l2 = armSegments[1].length;
    double l1 = armSegments[0].length;
    double cos2 = newAngleCos;
    double ex = targetPoint.x();
    double ey = targetPoint.y();
    double angle1 = (-(l2 * sin2 * ex) + ((l1 + (l2 * cos2)) * ey)) /
             ((l2 * sin2 * ey) + ((l1 + (l2 * cos2)) * ex));

//    armSegments[0].calculateEndPoint(armSegments[0].beginPoint,armSegments[0].length,angle1);
}

