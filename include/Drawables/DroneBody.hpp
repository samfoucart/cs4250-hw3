#ifndef __DRONE_BODY_HPP__
#define __DRONE_BODY_HPP__

#include "Drawable.hpp"
#include "drone.h"
#include "DroneRotor.hpp"

namespace cs4250 {
std::stack<mat4> mvStack;
mat4 modelView;

class DroneBody: public Drawable {
public:
    DroneBody();
    std::vector<DroneRotor> droneRotors;
    const mat4 defaultScale = Scale(.25, .25, .5);
    virtual void draw();

    void setWingTheta(GLfloat wingTheta);

private:
    GLfloat wingTheta;
}; // end class


inline void DroneBody::setWingTheta(GLfloat wingTheta) {
    this->wingTheta = wingTheta;
    for(size_t i = 0; i < droneRotors.size(); ++i) {
        droneRotors[i].setWingTheta(wingTheta);
    }
}

inline DroneBody::DroneBody() {
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
    droneRotors.push_back(DroneRotor(DroneRotor::TOP_LEFT));
    droneRotors.push_back(DroneRotor(DroneRotor::TOP_RIGHT));
    droneRotors.push_back(DroneRotor(DroneRotor::BOTTOM_LEFT));
    droneRotors.push_back(DroneRotor(DroneRotor::BOTTOM_RIGHT));                   
}

inline void DroneBody::draw() {
    mvStack.push(modelView);
    modelView = transformation * modelView;

    // Rotate everything down slightly and counterclockwise
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, modelView);
    glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines

    modelView = mvStack.top();
    mvStack.pop();

    for(auto x: droneRotors) {
        x.draw();
    }
}

} // end namespace

#endif