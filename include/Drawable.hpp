#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <vector>
#include "Angel.h"


namespace cs4250 {
class Drawable {
public:

    virtual ~Drawable();

    std::vector<vec4> points;
    std::vector<vec3> normals;
    mat4 transformation;
    virtual void draw() = 0;
    GLint bufferPosition = 0;
    virtual void turnRight();
    virtual void turnLeft();
    virtual void moveForward();
    virtual void pitchUp();

    GLfloat pitch = 0;
    GLfloat yaw = 0;
    GLfloat roll = 0;
    vec4 position = vec4(0, 0, 0, 1);
};
}

#endif