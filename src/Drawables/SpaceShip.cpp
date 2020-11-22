//
// Created by Sam Foucart on 11/19/20.
//

#include "Drawables/SpaceShip.h"

void cs4250::SpaceShip::draw() {
    SpaceProgram::mvStack.push(SpaceProgram::modelView);
    SpaceProgram::modelView = SpaceProgram::modelView * Translate(position) * RotateY(roll) * RotateX(pitch);
    //SpaceProgram::modelView = SpaceProgram::modelView * RotateX(90);
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_TRUE, SpaceProgram::modelView);

    nose.draw();
    body.draw();
    jet.draw();
    cockPit.draw();
    //rightWing.draw();
    //leftWing.draw();

    SpaceProgram::modelView = SpaceProgram::mvStack.top();
    SpaceProgram::mvStack.pop();
}

cs4250::SpaceShip::SpaceShip(GLint bufferPosition){
    totalPoints = 0;
    totalNormals = 0;

    this->bufferPosition = bufferPosition;

    nose.transformation = RotateZ(180) * Translate(0, 0, -1.5) * Scale(1, .2, 1) * RotateX(-90);
    nose.bufferPosition = bufferPosition + totalPoints;
    totalPoints += nose.points.size();
    totalNormals += nose.normals.size();

    body.transformation = RotateZ(180) * Translate(0, 0, .5) * Scale(1, .2, 2) * RotateX(-90);
    body.bufferPosition = bufferPosition + totalPoints;
    totalPoints += body.points.size();
    totalNormals += body.normals.size();


    jet.transformation = Translate(0, 0, .5) * Scale(1, .2, .5);
    jet.bufferPosition = bufferPosition + totalPoints;
    totalPoints += jet.points.size();
    totalNormals += jet.normals.size();

    cockPit.transformation = Translate(0, .15, -1) * Scale(.5, .1, .5);
    cockPit.bufferPosition = bufferPosition + totalPoints;
    totalPoints += cockPit.points.size();
    totalNormals += cockPit.normals.size();

    //rightWing.transformation = Translate(1, 0, 0) * Scale(.5, .1, .25);
    //leftWing.transformation = Translate(-1, 0, 0) * Scale(.5, .1, .25);
}

cs4250::SpaceShip::~SpaceShip() {

}

GLint cs4250::SpaceShip::getTotalPoints() const {
    return totalPoints;
}

GLint cs4250::SpaceShip::getTotalNormals() const {
    return totalNormals;
}

std::vector<vec4> cs4250::SpaceShip::getAllPoints() const {
    std::vector<vec4> allPoints;
    allPoints.insert(allPoints.end(), nose.points.begin(), nose.points.end());

    allPoints.insert(allPoints.end(), body.points.begin(), body.points.end());

    allPoints.insert(allPoints.end(), jet.points.begin(), jet.points.end());

    allPoints.insert(allPoints.end(), cockPit.points.begin(), cockPit.points.end());
    return allPoints;

}

std::vector<vec3> cs4250::SpaceShip::getAllNormals() const {
    std::vector<vec3> allNormals;
    allNormals.insert(allNormals.end(), nose.normals.begin(), nose.normals.end());

    allNormals.insert(allNormals.end(), body.normals.begin(), body.normals.end());

    allNormals.insert(allNormals.end(), jet.normals.begin(), jet.normals.end());

    allNormals.insert(allNormals.end(), cockPit.normals.begin(), cockPit.normals.end());
    return allNormals;
}

void cs4250::SpaceShip::turnRight() {
    roll -= 15;
}

void cs4250::SpaceShip::turnLeft() {
    roll += 15;
}

void cs4250::SpaceShip::moveForward() {
    vec4 pointing = RotateY(roll) * RotateX(pitch) * vec4(0, 0, -1, 0);
    position = Translate(pointing) * position;
}

void cs4250::SpaceShip::pitchUp() {
    pitch += 15;
}

void cs4250::SpaceShip::update(GLfloat elapsedTime) {

}


