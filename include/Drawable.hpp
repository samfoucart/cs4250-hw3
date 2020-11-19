#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

#include <vector>
#include "Angel.h"


namespace cs4250 {
class Drawable {
public:

    virtual ~Drawable();

    std::vector<vec4> points;
    mat4 transformation;
    virtual void draw() = 0;
    GLint bufferPosition = 0;
};
}

#endif