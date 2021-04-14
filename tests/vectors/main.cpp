#include <vector>

#include "triangle.hpp"

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
