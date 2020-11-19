//
// Created by Sam Foucart on 11/19/20.
//

#include "Drawables/Cone.h"

namespace cs4250 {
    Cone::Cone() = default;

    void Cone::triangle(vec4 a, vec4 b, vec4 c, vec3 na, vec3 nb, vec3 nc) {
        normals.push_back(na);
        points.push_back(a);
        normals.push_back(nb);
        points.push_back(b);
        normals.push_back(nc);
        points.push_back(c);
    }

    void Cone::cone () {
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

    void Cone::draw()  {
        SpaceProgram::mvStack.push(SpaceProgram::modelView);
        SpaceProgram::modelView = SpaceProgram::modelView * Translate(.5, .5, 0) * RotateX(-30) * Scale(.25, .25, .25);
        glUniformMatrix4fv(cs4250::view_loc, 1, GL_TRUE, SpaceProgram::modelView);

        glDrawArrays(GL_TRIANGLES, bufferPosition, points.size());
        SpaceProgram::modelView = SpaceProgram::mvStack.top();
        SpaceProgram::mvStack.pop();
    }

    Cone::~Cone() = default;
}