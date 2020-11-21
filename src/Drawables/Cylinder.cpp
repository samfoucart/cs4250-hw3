//
// Created by Sam Foucart on 11/19/20.
//

#include "Drawables/Cylinder.h"

namespace cs4250 {
// Build a triangle from three points.
void Cylinder::triangle(vec4 a, vec4 b, vec4 c, vec3 na, vec3 nb, vec3 nc) {
    //   compute its face normal
    //  vec4 u = b - a;
    //  vec4 v = c - b;

    //  vec3 normal = normalize(cross(u, v));

    // Following for flat shading of triangles.
    normals.push_back(na);
    points.push_back(a);
    normals.push_back(nb);
    points.push_back(b);
    normals.push_back(nc);
    points.push_back(c);
}

// Unit cylinder, base on x-z plane, height 1.
void Cylinder::cylinder ()
{
    // generate circle of points
    // Bottom
    vec4 currb=vec4(1, 0, 0, 1);// point
    vec3 currn=vec3(1, 0, 0); // vec
    vec4 prevb=vec4(1, 0, 0, 1);// previous point
    vec3 prevn=vec3(1, 0, 0);
    // Top
    vec4 currt=vec4(1, 1, 0, 1);// point
    vec4 prevt=vec4(1, 1, 0, 1);// previous point
    float incr=2*M_PI/21.0;
    // ??
    prevt.x=prevb.x=cos(0);
    prevt.z=prevb.z=sin(0);
    prevn=vec3(prevt.x, prevt.y, prevt.z);

    for (GLfloat delta=incr; delta<=2*M_PI; delta+=incr) {
        currt.x=currb.x=cos(delta);
        currt.z=currb.z=sin(delta);
        currn=vec3(currt.x, currt.y, currt.z);
        triangle(currb, prevb, currt, currn, prevn, currn);
        triangle(prevb, currt, prevt, prevn, currn, prevn);

        //    triangle(vertex, prev, curr, normv, normprev, normcurr);
        prevb=currb;
        prevt=currt;
        prevn=currn;
    }
}

void Cylinder::draw()  {
    SpaceProgram::mvStack.push(SpaceProgram::modelView);
    SpaceProgram::modelView = SpaceProgram::modelView * transformation;
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_TRUE, SpaceProgram::modelView);

    glDrawArrays(GL_TRIANGLES, bufferPosition, points.size());
    SpaceProgram::modelView = SpaceProgram::mvStack.top();
    SpaceProgram::mvStack.pop();
}

    Cylinder::Cylinder() {
        cylinder();
    }

    Cylinder::~Cylinder() {

    }
}