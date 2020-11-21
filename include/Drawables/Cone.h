//
// Created by Sam Foucart on 11/18/20.
//
#include "Drawable.hpp"
#include "Angel.h"
#include "SpaceProgram.hpp"

#ifndef HW2_CONE_H
#define HW2_CONE_H



namespace cs4250 {
class Cone: public Drawable {
public:
    Cone();
    ~Cone();

    // Build a triangle from three points.
    void triangle(vec4 a, vec4 b, vec4 c, vec3 na, vec3 nb, vec3 nc);

    // Unit cone, vertex at 0, 1, 0. base on x-z plane
    void cone ();

    void draw() override;
};
}

#endif //HW2_CONE_H
