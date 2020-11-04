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
    DroneBody() : DroneBody(vec3(0, 0, 0)) {};
    DroneBody(vec3 position);
    std::vector<DroneRotor> droneRotors;
    DroneLauncher launcher;

    GLfloat missleTime;
    bool missleVisible;
    DroneLauncher missle;
    void fireMissle();

    const mat4 defaultScale = Scale(.25, .25, .5);
    virtual void draw();

    void setWingTheta(GLfloat wingTheta);

    vec3 position = vec3(0, 0, 0);

    const vec4 REDVEC = vec4(1, 0, 0, 1);
    const vec4 BLUEVEC = vec4(0, 0, 1, 1);
    const vec4 HOVERVEC = vec4(.5, 0, .5, 1);
    const vec4 SELECTEDVEC = vec4(0, 1, 0, 1);

    vec4 currentColor = HOVERVEC;
    enum Team{GOOD, BAD} team = GOOD;
    bool selected = false;

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

inline DroneBody::DroneBody(vec3 position) {
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
    this->position = position;                   
}

inline void DroneBody::draw() {
    mvStack.push(modelView);
    transformation = defaultScale * transpose(Translate(position));
    modelView = transformation * modelView;

    // Rotate everything down slightly and counterclockwise
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, modelView);

    glUniform4f(cs4250::color_loc, currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
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