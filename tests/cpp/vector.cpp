#include <vector>
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

int main(int argc, char const *argv[])
{
    std::vector<Triangle> tri_vec1;
    std::cout << "Without reserve:" << std::endl;

    tri_vec1.push_back({1, 2, 3});
    tri_vec1.push_back({4, 5, 6});
    tri_vec1.push_back({7, 8, 9});

    std::cout << "With reserve:" << std::endl;

    std::vector<Triangle> tri_vec2;
    tri_vec2.reserve(3);

    tri_vec1.push_back({1, 2, 3});
    tri_vec1.push_back({4, 5, 6});
    tri_vec1.push_back({7, 8, 9});

    std::cout << "With reserve and emplace:" << std::endl;
    std::vector<Triangle> tri_vec3;
    tri_vec3.reserve(3);

    tri_vec3.emplace_back(1, 2, 3);
    tri_vec3.emplace_back(1, 2, 3);
    tri_vec3.emplace_back(1, 2, 3);

    return 0;
}
