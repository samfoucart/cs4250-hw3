//
// Created by Sam Foucart on 11/18/20.
//
#include "Drawable.hpp"
#include "Angel.h"
#include "SpaceProgram.hpp"

#ifndef HW2_SPHERE_H
#define HW2_SPHERE_H


namespace cs4250 {
    //extern std::stack<mat4> mvStack;
    class Sphere: public Drawable {
    public:
        std::vector<vec4> points;
        std::vector<vec3> normals;

        Sphere() {

        }
        inline void triangle(const vec4& a, const vec4& b, const vec4& c) {
          vec3  normal = normalize(cross(b - a, c - b));

          normals.push_back(normal);  points.push_back(a);
          normals.push_back(normal);  points.push_back(b);
          normals.push_back(normal);  points.push_back(c);
        }

        inline void divide_triangle(const vec4& a, const vec4& b,
                             const vec4& c, int count)
        {
            if (count > 0) {
                vec4 v1 = unit(a + b);
                vec4 v2 = unit(a + c);
                vec4 v3 = unit(b + c);
                divide_triangle( a, v1, v2, count - 1);
                divide_triangle( c, v2, v3, count - 1);
                divide_triangle( b, v3, v1, count - 1);
                divide_triangle(v1, v3, v2, count - 1);
            }
            else {
                triangle(a, b, c);
            }
        }

        inline vec4 unit(const vec4& p)
        {
            float len = p.x*p.x + p.y*p.y + p.z*p.z;

            vec4 t;
            if (len > DivideByZeroTolerance) {
                t = p / sqrt(len);
                t.w = 1.0;
            }

            return t;
        }

        inline void tetrahedron(int count)
        {
            vec4 v[4] = {
                    vec4(0.0, 0.0, 1.0, 1.0),
                    vec4(0.0, 0.942809, -0.333333, 1.0),
                    vec4(-0.816497, -0.471405, -0.333333, 1.0),
                    vec4(0.816497, -0.471405, -0.333333, 1.0)
            };

            divide_triangle(v[0], v[1], v[2], count);
            divide_triangle(v[3], v[2], v[1], count);
            divide_triangle(v[0], v[3], v[1], count);
            divide_triangle(v[0], v[2], v[3], count);
        }


        inline void draw() {
            //cs4250::mvStack.push(modelView);
            //cs4250::modelView = cs4250::modelView * Scale(.25, .25, .25);
            glUniformMatrix4fv(cs4250::view_loc, 1, GL_TRUE, cs4250::SpaceProgram::modelView);

            glDrawArrays(GL_TRIANGLES, 0, points.size());
            //modelView = mvStack.top();
            //mvStack.pop();
        }
    };
}


#endif //HW2_SPHERE_H
