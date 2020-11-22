//
// Created by Sam Foucart on 11/19/20.
//

#ifndef HW2_SPACESHIP_H
#define HW2_SPACESHIP_H


#include "Drawable.hpp"
#include "Angel.h"
#include "Cone.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cube.h"


namespace cs4250 {
    class SpaceShip: public Drawable {
    public:
        SpaceShip(GLint t_bufferPosition = 0);
        ~SpaceShip();
        GLint getTotalPoints() const;
        GLint getTotalNormals() const;
        std::vector<vec4> getAllPoints() const;
        std::vector<vec3> getAllNormals() const;
        void draw() override;
        void update() override;
        void turnRight() override;
        void turnLeft() override;
        void moveForward() override;
        void pitchUp() override;

    private:
        Cone nose;
        Cylinder body;
        Cube rightWing;
        Cube leftWing;
        Sphere jet = Sphere(5);
        Sphere cockPit = Sphere(5);
        GLint totalNormals;
        GLint totalPoints;
        GLfloat pitch = 0;
        GLfloat yaw = 0;
        GLfloat roll = 0;
        vec4 position = vec4(0, 0, 0, 1);

    };

}


#endif //HW2_SPACESHIP_H
