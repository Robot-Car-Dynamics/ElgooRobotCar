#include "PositionTracking.h"
#include "Arduino.h" 
void PositionTracking::updatePosition(int accel, int timeDiff) {
    // the following represents updating the model
    // update based on previous state
    int predictedPositionX = positionX + velocityX * timeDiff;
    int predictedVelocityX = velocityX;

    // update based on measured acceleration
    predictedPositionX += 0.5 * accel * (timeDiff * timeDiff);
    predictedVelocityX += accel * timeDiff;

    // increase uncertainty due to model/process noise
    posXUncertainty += processNoisePosX;
    velXUncertainty += processNoiseVelX;

    // calculate kalman gain 
    float kalmanGain = posXUncertainty / (posXUncertainty + measurementNoise);

    // find z using simple noise generation
    float z = positionX + generateNoise();

    // correct position
    positionX = predictedPositionX + kalmanGain * (z - predictedPositionX);

    // correct velocity (indirectly)
    velocityX = predictedVelocityX + kalmanGain * (z - predictedPositionX) / timeDiff;

    // reduce uncertainty after measurement
    posXUncertainty = (1 - kalmanGain) * posXUncertainty;
    velXUncertainty = (1 - kalmanGain) * velXUncertainty;
}

PositionTracking::PositionTracking(int posx, int velX) {
    positionX = posx;
    velocityX = velX;
}

void PositionTracking::getLocSpe(int* pos, int* vel) {
    *pos = positionX;
    *vel = velocityX;
}

float PositionTracking::generateNoise() {
    // Simple noise generation using Arduino's random function
    // This approximates Gaussian noise
    float noise = 0.0;
    for (int i = 0; i < 12; i++) {
        noise += random(-1000, 1000) / 1000.0;
    }
    noise = (noise - 6.0) * sqrt(measurementNoise);
    return noise;
    //return (random(-100, 100) / 100.0) * measurementNoise;

}