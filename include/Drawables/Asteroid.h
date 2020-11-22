//
// Created by Sam Foucart on 11/21/20.
//

#ifndef HW2_ASTEROID_H
#define HW2_ASTEROID_H
#include "Drawable.hpp"
#include "Angel.h"
#include "SpaceProgram.hpp"

namespace cs4250 {
    class Asteroid: public Drawable {
    public:
        Asteroid(int count);
        ~Asteroid();

        void triangle(const vec4& a, const vec4& b, const vec4& c);

        void divide_triangle(const vec4& a, const vec4& b,
                             const vec4& c, int count);

        vec4 unit(const vec4& p);

        void tetrahedron(int count);

        void draw() override;
        void update() override;
    };
}


#endif //HW2_ASTEROID_H
