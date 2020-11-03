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
    DroneRotor topLeftRotor = DroneRotor(DroneRotor::TOP_LEFT);
    DroneRotor topRightRotor = DroneRotor(DroneRotor::TOP_RIGHT);
    DroneRotor bottomLeftRotor = DroneRotor(DroneRotor::BOTTOM_LEFT);
    DroneRotor bottomRightRotor = DroneRotor(DroneRotor::BOTTOM_RIGHT);
    const mat4 defaultScale = Scale(.25, .25, .5);
    virtual void draw();

    void setWingTheta(GLfloat wingTheta);

private:
    GLfloat wingTheta;
}; // end class


inline void DroneBody::setWingTheta(GLfloat wingTheta) {
    this->wingTheta = wingTheta;
    topLeftRotor.wingTheta = this->wingTheta;
    topRightRotor.wingTheta = this->wingTheta;
    bottomLeftRotor.wingTheta = this->wingTheta;
    bottomRightRotor.wingTheta = this->wingTheta;
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
}

inline void DroneBody::draw() {
    mvStack.push(modelView);
    modelView = transformation * modelView;

    // Rotate everything down slightly and counterclockwise
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, modelView);
    glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines

    modelView = mvStack.top();
    mvStack.pop();
    topLeftRotor.draw();
    topRightRotor.draw();
    bottomLeftRotor.draw();
    bottomRightRotor.draw();

    

}

} // end namespace

#endif