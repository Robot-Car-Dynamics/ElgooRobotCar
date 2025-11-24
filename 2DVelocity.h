#ifndef TWODVELOCITY
#define TWODVELOCITY

// Use Arduino.h for types and math functions instead of math.h/stdint.h
#include <Arduino.h>

namespace motion {
    // Convert velocity to X and Y components based on heading angle
    inline void velPerAxis(float speed, float headingDeg, float& velX, float& velY) {
        float radians = (3.14159 / 180.0) * headingDeg;
        velY = speed * cos(radians); // flip these assignments if heading is displacement from x axis, rather than from forward at start
        velX = speed * sin(radians);
    }
    
    // Convert LSB accelerometer reading to meters per second squared
    // Assuming MPU6050 default range of ±2g (16384 LSB/g)
    inline float lsbToMps(int16_t accelLSB) {
        const float LSB_PER_G = 16384.0;
        const float G_TO_MPS2 = 9.81;
        return (accelLSB / LSB_PER_G) * G_TO_MPS2;
    }
}

#endif