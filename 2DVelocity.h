#ifndef TWODVELOCITY
#define TWODVELOCITY

// #include<cmath>
namespace motion {
    inline void velPerAxis(float speed, float headingDeg, float& velX, float& velY) {
        float radians = (3.14159 / 180.0) * headingDeg;
        velY = speed * cos(radians); // flip these assignments if heading is displacement from x axis, rather than from forward at start
        velX = speed * sin(radians);
    }

    inline float lsbToMps (int rawAccel) {
        // Converts from raw LSB to meters per second squared
        return (rawAccel / 16384.0) * 9.81;  // for ±2g setting
    }
}

#endif