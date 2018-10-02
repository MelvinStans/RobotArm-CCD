//
// Created by Melvin Stans on 15/09/2018.
//

#include <iostream>
#include "ArmSegment.h"
#include "Arm.h"

void Arm::generateArm() {
    std::cout << "Generating arm with " << segmentCount << " segments" << std::endl;

    // Make first segment
    armSegments[0] = ArmSegment(Vector3d(200,0,0),50,0);

    // Make remaing segments
    int total = 0;
    for (int j = 1; j < segmentCount; ++j) {
        total = total + segmentLengths[j];
        armSegments[j] = ArmSegment(Vector3d(200,total,0),segmentLengths[j],0);
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

void Arm::updateArm(Vector3d targetPoint) {

    int i = segmentCount;
    int tries = 0;
    int maxtries = 30;
    do{
        // offset axis with beginpoint
        Vector3d root = armSegments[i].beginPoint;
        Vector3d curEnd = armSegments[i].endPoint;
        Vector3d targetVector;
        Vector3d curVector;

        curVector.x() = curEnd.x() - root.x();
        curVector.y() = curEnd.y() - root.y();
        curVector.z() = curEnd.z() - root.z();

        targetVector.x() = targetPoint.x() - root.x();
        targetVector.y() = targetPoint.y() - root.y();
        targetVector.z() = 0;

        // normalize

        curVector.normalize();
        targetVector.normalize();

        double cosAngle = targetVector.dot(curVector);
        if (cosAngle < 0.99) {
            Vector3d cross = targetVector.cross(curVector);
            double angleDeg = acos(cosAngle);
            if (cross.z() > 0.0) {
                angleDeg = angleDeg - armSegments[i].angle;
                std::cout << "angleDeg" << angleDeg << std::endl;
                armSegments[i].calculateEndPoint(root, armSegments[i].length, angleDeg);
                armSegments[i+1].beginPoint = armSegments[i].endPoint;
            } else if (cross.z() < 0.0) {
                angleDeg = angleDeg + armSegments[i].angle;
                std::cout << "angleDeg" << angleDeg << std::endl;
                armSegments[i].calculateEndPoint(root, armSegments[i].length, angleDeg);
                armSegments[i+1].beginPoint = armSegments[i].endPoint;
            }
        }
        if (--i < 0) {
            i = segmentCount;
        }
    } while (tries++ < maxtries);

}

