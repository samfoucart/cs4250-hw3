//
// Created by Sam Foucart on 11/19/20.
//

#include "Drawables/Cube.h"
namespace cs4250 {
cs4250::Cube::Cube() {
    colorcube();
}

cs4250::Cube::~Cube() {

}

void cs4250::Cube::draw() {
    SpaceProgram::mvStack.push(SpaceProgram::modelView);
    SpaceProgram::modelView = SpaceProgram::modelView;
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_TRUE, SpaceProgram::modelView);

    glDrawArrays(GL_TRIANGLES, bufferPosition, points.size());
    SpaceProgram::modelView = SpaceProgram::mvStack.top();
    SpaceProgram::mvStack.pop();
}

//----------------------------------------------------------------------------
// generate 12 triangles: 36 vertices and 36 normals
void Cube::colorcube() {
    MyQuad(1, 0, 3, 2);
    MyQuad(2, 3, 7, 6);
    MyQuad(3, 0, 4, 7);
    MyQuad(6, 5, 1, 2);
    MyQuad(4, 5, 6, 7);
    MyQuad(5, 4, 0, 1);
}

void Cube::MyQuad(int a, int b, int c, int d) {
    // Initialize temporary vectors along the MyQuad's edge to
    //   compute its face normal
    vec4 u = vertices[b] - vertices[a];
    vec4 v = vertices[c] - vertices[b];

    vec3 normal = normalize(cross(u, v));

    normals.push_back(normal);
    points.push_back(vertices[a]);

    normals.push_back(normal);
    points.push_back(vertices[b]);

    normals.push_back(normal);
    points.push_back(vertices[c]);

    normals.push_back(normal);
    points.push_back(vertices[a]);

    normals.push_back(normal);
    points.push_back(vertices[c]);

    normals.push_back(normal);
    points.push_back(vertices[d]);

}

    void Cube::update(GLfloat elapsedTime) {

    }

}