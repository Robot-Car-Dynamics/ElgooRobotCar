#ifndef TWODVELOCITY
#define TWODVELOCITY

#include<cmath>
namespace motion {
    inline void velPerAxis(float speed, float headingDeg, float& velX, float& velY) {
        float radians = (3.14159 / 180.0) * headingDeg;
        velY = speed * std::cos(radians); // flip these assignments if heading is displacement from x axis, rather than from forward at start
        velX = speed * std::sin(radians);
    }
}

#endif