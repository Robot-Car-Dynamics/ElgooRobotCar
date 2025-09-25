#ifndef POSITIONTRACKING
#define POSITIONTRACKING

// Remove std library dependencies for Arduino compatibility
// #include <utility>
// #include <random>

class PositionTracking {
public:
    PositionTracking(int posx, int velX);
    ~PositionTracking(); // not implemented for now
    void updatePosition(int accel, int timeDiff);
    void getLocSpe(int* pos, int* vel); // Modified to work without std::pair
    
private:
    // state consists of both position and velocity
    int positionX = 0;
    int velocityX = 0;

    // uncertainty in position and velocity. 
    // float between 0 and 1
    float posXUncertainty = 1.0;
    float velXUncertainty = 1.0;

    // uncertainty in model
    float processNoisePosX = 0.0001;
    float processNoiseVelX = 0.0001;

    // uncertainty in observations
    float measurementNoise = 0.1;
    
    // Simple random number generation for Arduino
    float generateNoise();
};

#endif