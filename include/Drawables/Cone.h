//
// Created by Sam Foucart on 11/18/20.
//
#include "Drawable.hpp"
#include "Angel.h"
#include "SpaceProgram.hpp"

#ifndef HW2_CONE_H
#define HW2_CONE_H



namespace cs4250 {
    //std::stack<mat4> mvStack;
    //std::stack<mat4> mvStack;
class Cone: public Drawable {
public:
    std::vector<vec4> points;
    std::vector<vec3> normals;

    Cone() {
    /*
        points.push_back(vec4(-1,0, 0,1));
        points.push_back(vec4(1,0, 0,1));
        points.push_back(vec4(0,1, 0,1));
        normals.push_back(vec3(0,0, 1));
        normals.push_back(vec3(0,0, 1));
        normals.push_back(vec3(0,0, 1));
*/
    }

    // Build a triangle from three points.
    inline void triangle(vec4 a, vec4 b, vec4 c, vec3 na, vec3 nb, vec3 nc)
    {
        normals.push_back(na); points.push_back(a);
        normals.push_back(nb); points.push_back(b);
        normals.push_back(nc); points.push_back(c);
    }

    // Unit cone, vertex at 0, 1, 0. base on x-z plane
    inline void cone ()
    {

        vec4 vertex=vec4(0, 2, 0, 1);
        // generate circle of points
        vec4 curr=vec4(sin(0), 0, cos(0), 1);              // point
        vec4 prev=curr;
        float incr=2.0*M_PI/51.0;                          // controls how many facets the cone will have.
        vec3 tan=normalize(cross(vertex-curr, curr));;     // current tangent direction
        vec3 normcurr=normalize(cross(tan, vertex-curr));  // current normal
        vec3 normprev=normcurr;
        vec3 normv;                                        // normal at vertex for this triangle.
        for (GLfloat delta=incr; delta<2*M_PI+incr; delta+=incr) {
            curr.x=sin(delta);
            curr.z=cos(delta);
            tan=normalize(cross(vertex-curr, curr));
            normcurr=normalize(cross(tan, vertex-curr));
            normv=normalize(normcurr+normprev);
            triangle(vertex, prev, curr, normv, normprev, normcurr);
            prev=curr;
            normprev=normcurr;
        }

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

#endif //HW2_CONE_H
