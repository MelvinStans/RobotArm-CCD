//
// Created by Melvin Stans on 15/09/2018.
//

#include <iostream>
#include "ArmSegment.h"
#include "Arm.h"
double simplifyAngle(double angle)
{
    angle = fmod(angle,(2.0*M_PI));
    if( angle < -M_PI )
        angle += (2.0 * M_PI);
    else if( angle > M_PI )
        angle -= (2.0 * M_PI);
    return angle;
}

Arm::Arm(int sLength, int sCount) {
    this->segmentLength = sLength;
    this->segmentCount = sCount;

    // Generate segments
    // Make first segment
    this->armSegments[0] = ArmSegment(Vector3d(200,0,0),segmentLength,0);

    // Make remaining segments
    int total = 0;
    for (int j = 1; j < segmentCount; ++j) {
        total = total + segmentLength;
        this->armSegments[j] = ArmSegment(Vector3d(200,total,0),segmentLength,0);
    }
}

void Arm::moveToPoint(Vector2d targetPoint){

    std::cout<<"tgp\n"<<targetPoint<<std::endl;

    double arrivalDist = 2;
    double epsilon = 0.0001;
    double trivialArcLength = 0.00001;

    int numSeg = segmentCount;

    double arrivalDistSqr = arrivalDist*arrivalDist;

    double endX = armSegments[2].endPoint.x();
    double endY = armSegments[2].endPoint.y();

    double targetX = targetPoint.x();
    double targetY = targetPoint.y();

//    // convert some bones
//    for( int i = 1; i < segmentCount; ++i ){
//        ArmSegment prev = armSegments[i-1];
//        ArmSegment curSeg = armSegments[i];
//
//        curSeg.endPoint.x() = prev.endPoint.x() + prev.cosAngle*curSeg.endPoint.x()-prev.sinAngle*curSeg.endPoint.y();
//        curSeg.endPoint.y() = prev.endPoint.y() + prev.sinAngle*curSeg.endPoint.y() + prev.cosAngle*curSeg.endPoint.y();
//        curSeg.angle = prev.angle + curSeg.angle;
//        curSeg.cosAngle = cos(curSeg.angle);
//        curSeg.sinAngle = sin(curSeg.angle);
//    }

    std::cout<<"endp\n"<<armSegments[2].endPoint<<std::endl;

    bool modifiedBones = false;
    do {
        for (int i = numSeg; i >= 0; --i) {
            printf("bone cycle%i\n", i);
            // Get the vector from the current bone to the end effector position.
            double curToEndX = endX - armSegments[i].endPoint.x();
            double curToEndY = endY - armSegments[i].endPoint.y();
            double curToEndMag = sqrt(curToEndX * curToEndX + curToEndY * curToEndY);

            std::cout << "curtoendx" << curToEndX << std::endl;
            std::cout << "curtoendy" << curToEndY << std::endl;
            std::cout << "curtoendmag" << curToEndMag << std::endl;

            // Get the vector from the current bone to the target position.
            double curToTargetX = targetX - armSegments[i].endPoint.x();
            double curToTargetY = targetY - armSegments[i].endPoint.y();
            double curToTargetMag = sqrt(curToTargetX * curToTargetX + curToTargetY * curToTargetY);

            std::cout << "curtotarx" << curToTargetX << std::endl;
            std::cout << "curtotary" << curToTargetY << std::endl;
            std::cout << "curtotarmag" << curToTargetMag << std::endl;

            // Get rotation to place the end effector on the line from the current
            // joint position to the target postion.
            double cosRotAng;
            double sinRotAng;
            double endTargetMag = (curToEndMag * curToTargetMag);

            std::cout << "endTargetMag" << endTargetMag << std::endl;

            if (endTargetMag <= epsilon) {
                cosRotAng = 1;
                sinRotAng = 0;
            } else {
                cosRotAng = (curToEndX * curToTargetX + curToEndY * curToTargetY) / endTargetMag;
                sinRotAng = (curToEndX * curToTargetY - curToEndY * curToTargetX) / endTargetMag;
            }

            std::cout << "cosRotAng" << cosRotAng << std::endl;
            std::cout << "sinRotAng" << sinRotAng << std::endl;

            // Clamp the cosine into range when computing the angle (might be out of range
            // due to floating point error).

            double rotAng = cos(fmax(-1, fmin(1, cosRotAng)));
            if (sinRotAng < 0.0) {
                rotAng = -rotAng;
            }

            std::cout << "rotAng" << rotAng << std::endl;

            // Rotate the end effector position.
            endX = armSegments[i].endPoint.x() + cosRotAng * curToEndX - sinRotAng * curToEndY;
            endY = armSegments[i].endPoint.y() + sinRotAng * curToEndX + cosRotAng * curToEndY;

            std::cout << "curtoendx" << curToEndX << std::endl;
            std::cout << "curtoendy" << curToEndY << std::endl;

            // Rotate the current bone in local space (this value is output to the user)
            armSegments[i].angle = simplifyAngle(armSegments[i].angle + rotAng);

            std::cout << "angle" << armSegments[i].angle << std::endl;

            for (int j = 0; j < numSeg; ++j) {
                armSegments[i].calculateEndPoint(armSegments[i].beginPoint,armSegments[i].angle);
                if (i != 0){
                    armSegments[i].move(armSegments[i-1].endPoint);
                }
            }


            //TODO move arms to beginpoint

            // Check for termination
            double endToTargetX = (targetX - endX);
            double endToTargetY = (targetY - endY);
            if (endToTargetX * endToTargetX + endToTargetY * endToTargetY <= arrivalDistSqr) {
                // We found a valid solution.
                printf("success\n");
                modifiedBones = false;
            }
            // Track if the arc length that we moved the end effector was
            // a nontrivial distance.
//            if (!modifiedBones && abs(rotAng) * curToEndMag > trivialArcLength) {
//                modifiedBones = true;
//            }
        }
        // We failed to find a valid solution during this iteration.
//        if( modifiedBones ) {
//            printf("processing\n");
//        } else {
//            printf("failed\n");
//        }
    }while (modifiedBones);



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
                armSegments[i].calculateEndPoint(root, angleDeg);
                armSegments[i+1].beginPoint = armSegments[i].endPoint;
            } else if (cross.z() < 0.0) {
                angleDeg = angleDeg + armSegments[i].angle;
                std::cout << "angleDeg" << angleDeg << std::endl;
                armSegments[i].calculateEndPoint(root, angleDeg);
                armSegments[i+1].beginPoint = armSegments[i].endPoint;
            }
        }
        if (--i < 0) {
            i = segmentCount;
        }
    } while (tries++ < maxtries);

}

