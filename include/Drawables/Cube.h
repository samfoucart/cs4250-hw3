//
// Created by Sam Foucart on 11/19/20.
//

#ifndef HW2_CUBE_H
#define HW2_CUBE_H


#include "Drawable.hpp"
#include "Angel.h"
#include "SpaceProgram.hpp"

namespace cs4250 {
class Cube: public Drawable {
public:
    std::vector<vec4> points;
    std::vector<vec3> normals;

    Cube();
    ~Cube();

    void MyQuad(int a, int b, int c, int d);
    void colorcube();
    void draw() override;

    // Vertices of a unit cube centered at origin, sides aligned with axes
    vec4 vertices[8] = {
            vec4(-0.5, -0.5,  0.5, 1.0),
            vec4(-0.5,  0.5,  0.5, 1.0),
            vec4( 0.5,  0.5,  0.5, 1.0),
            vec4( 0.5, -0.5,  0.5, 1.0),
            vec4(-0.5, -0.5, -0.5, 1.0),
            vec4(-0.5,  0.5, -0.5, 1.0),
            vec4( 0.5,  0.5, -0.5, 1.0),
            vec4( 0.5, -0.5, -0.5, 1.0)
    };
};
}


#endif //HW2_CUBE_H
