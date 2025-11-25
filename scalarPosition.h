#ifndef POSITIONTRACKING
#define POSITIONTRACKING

/* 
A class to keep track of the robot's position.
This version performs Kalman filtering through scalarized calculations
*/


class PositionTracking {
public:
    PositionTracking(float posX, float velX, float posXUncert, float velXUncert, float posY, float velY, float posYUncert, float velYUncert, float accelNoise);
    void updatePosition(float heading);
    float voltageToSpeed(float voltage);
    float getPosX();
    float getPosXUncert();
    float getPosY();
    float getPosYUncert();
    float getVelX();
    float getVelXUncert();
    float getVelY();
    float getVelYUncert();
private:
    float xPosition, xVelocity, xPosUncert, xVelUncert, yPosition, yVelocity, yPosUncert, yVelUncert, velMagnitude, accelNoise, xCovariance, yCovariance;
    unsigned long clockTime;
};


#endif