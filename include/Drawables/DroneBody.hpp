#ifndef __DRONE_BODY_HPP__
#define __DRONE_BODY_HPP__

#include "drone.h"
#include "Drawable.hpp"
#include "DroneRotor.hpp"
#include "DroneLauncher.hpp"

namespace cs4250 {
std::stack<mat4> mvStack;
mat4 modelView;

class DroneBody: public Drawable {
public:
    DroneBody();
    std::vector<DroneRotor> droneRotors;
    DroneLauncher launcher;

    GLfloat missleTime;
    bool missleVisible;
    DroneLauncher missle;
    void fireMissle();

    const mat4 defaultScale = Scale(.25, .25, .5);
    virtual void draw();

    void setWingTheta(GLfloat wingTheta);

private:
    GLfloat wingTheta;
}; // end class

inline void DroneBody::fireMissle() {
    missleVisible = true;
    missleTime = 0;
}

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

    

    for(auto x: droneRotors) {
        x.draw();
    }
    launcher.draw();

    if (missleTime > 5) {
      missleVisible = false;
    } else {
      missleTime += .1;
    }

    if (missleVisible) {
        missle.moveForward(missleTime);
        missle.draw();
    }

    modelView = mvStack.top();
    mvStack.pop();
}

} // end namespace

#endif