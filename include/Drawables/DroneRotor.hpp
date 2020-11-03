#ifndef __DRONE_ROTOR_HPP__
#define __DRONE_ROTOR_HPP__

#include "Drawable.hpp"
#include "drone.h"

namespace cs4250 {
extern std::stack<mat4> mvStack;
extern mat4 modelView;

class DroneRotor: public Drawable {
public:
    enum RotorPosition{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
    DroneRotor(RotorPosition rotorPosition = TOP_LEFT);
    const mat4 defaultScale = Scale(.2, .05, .1);
    virtual void draw();

    void setWingTheta(GLfloat wingTheta) { this->wingTheta = wingTheta; }
    
    RotorPosition getRotorPosition() { return rotorPosition; }
    void setRotorPosition(RotorPosition rotorPosition);
private:
    vec3 position;
    RotorPosition rotorPosition;
    GLfloat wingTheta = 0;
}; // end class


inline DroneRotor::DroneRotor(RotorPosition rotorPosition) {
    /**
     * Points used to draw a wireframe cube with GL_LINE_STRIP
     */ 
    points = std::vector<vec4>({
                        vec4(-1, -1, -1, 1),
                        vec4(1, -1, -1, 1),
                        vec4(1, 1, -1, 1),
                        vec4(-1, 1, -1, 1),
                        vec4(-1, -1, -1, 1),
                        vec4(1, 1, -1, 1),
                        vec4(1, 1, 1, 1),
                        vec4(-1, 1, -1, 1),
                        vec4(-1, 1, 1, 1),
                        vec4(1, 1, 1, 1),
                        vec4(1, -1, 1, 1),
                        vec4(-1, 1, 1, 1),
                        vec4(-1, -1, 1, 1),
                        vec4(1, -1, 1, 1),
                        vec4(1, 1, -1, 1),
                        vec4(1, -1, -1, 1),
                        vec4(1, -1, 1, 1),
                        vec4(-1, -1, -1, 1),
                        vec4(-1, -1, 1, 1),
                        vec4(-1, 1, 1, 1),
                        vec4(-1, -1, -1, 1),
                        vec4(-1, -1, -1, 1)
                        });

    transformation = defaultScale;
    setRotorPosition(rotorPosition);
}

inline void DroneRotor::setRotorPosition(RotorPosition rotorPosition) {
    this->rotorPosition = rotorPosition;
    switch (this->rotorPosition) {
    case TOP_LEFT:
        position = vec3(-.25, .25, .5);
        break;

    case TOP_RIGHT:
        position = vec3(.25, .25, .5);
        break;

    case BOTTOM_LEFT:
        position = vec3(-.25, .25, -.5);
        break;

    case BOTTOM_RIGHT:
        position = vec3(.25, .25, -.5);
        break;
    
    default:
        break;
    }
}

inline void DroneRotor::draw() {
    mvStack.push(modelView);
    mat4 translationMatrix = Translate(position);
    translationMatrix = transpose(translationMatrix);
    transformation = defaultScale * RotateY(wingTheta) * translationMatrix;
    modelView = transformation * modelView;

    glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, modelView);
    glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines

    modelView = mvStack.top();
    mvStack.pop();
}

} // end namespace

#endif