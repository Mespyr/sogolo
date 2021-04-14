#include <iostream>

struct Triangle {
    float x, y, z;
    Triangle(float x, float y, float z) 
        : x(x), y(y), z(z) {}

    Triangle(const Triangle& tri)
        : x(tri.x), y(tri.y), z(tri.z)
    {
        std::cout << "Copied!!" << std::endl;
    }

};