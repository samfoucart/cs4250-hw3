//
// Created by Sam Foucart on 11/18/20.
//
#include "Drawable.hpp"
#include "Angel.h"
#include "SpaceProgram.hpp"

#ifndef HW2_SPHERE_H
#define HW2_SPHERE_H


namespace cs4250 {
class Sphere: public Drawable {
public:
    std::vector<vec4> points;
    std::vector<vec3> normals;

    Sphere();
    ~Sphere();

    void triangle(const vec4& a, const vec4& b, const vec4& c);

    void divide_triangle(const vec4& a, const vec4& b,
                         const vec4& c, int count);

    vec4 unit(const vec4& p);

    void tetrahedron(int count);

    void draw() override;
};
}


#endif //HW2_SPHERE_H
