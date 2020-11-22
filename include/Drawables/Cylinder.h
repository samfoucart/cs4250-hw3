//
// Created by Sam Foucart on 11/19/20.
//

#ifndef HW2_CYLINDER_H
#define HW2_CYLINDER_H


#include "Drawable.hpp"
#include "Angel.h"
#include "SpaceProgram.hpp"


namespace cs4250 {
class Cylinder: public Drawable {
public:
    Cylinder();
    ~Cylinder();

    // Build a triangle from three points.
    void triangle(vec4 a, vec4 b, vec4 c, vec3 na, vec3 nb, vec3 nc);

    // Unit cone, vertex at 0, 1, 0. base on x-z plane
    void cylinder ();

    void draw() override;
    void update() override;
};
}


#endif //HW2_CYLINDER_H
