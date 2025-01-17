/**
 * @file drone.h
 * 
 * @author Sam Foucart sf241616@ohio.edu
 * 
 * @brief A drone where the user can click and drag to view from different angles
 * and push space to shoot a missle
 * 
 */
#ifndef __DRONE_H__
#define __DRONE_H__

#include <Angel.h>
#include <memory>
#include <stack>
#include "Drawable.hpp"

namespace cs4250 {
extern GLuint view_loc; // location of model_view_matrix
extern GLuint color_loc;
extern GLint projection_loc;

class SpaceProgram {
public:
    SpaceProgram();
    static void display();
    static mat4 modelView;
    static std::stack<mat4> mvStack;
    static std::vector<std::unique_ptr<Drawable>> drawables;
    static std::vector<vec4> allPoints;
    static std::vector<vec3> allNormals;
    static GLint bufferSize;
    static int spaceShipIndex;
    static vec4 cameraPosition;
    static GLfloat cameraPitch;
    static GLfloat cameraYaw;
    static GLfloat cameraRoll;
    static vec4 lightPosition;
    static vec4 defaultLightPos;
    static GLint lightLocation;
private:
    /**
     * Initializes the shaders and calls generate_points to initialize the program
     */
    static void init();


    static void createLevel();
};
}


extern "C" void display();
extern "C" void keyboard(unsigned char key, int x, int y);
extern "C" void mouse(int button, int state, int x, int y);
extern "C" void reshape_window(int width, int height);
extern "C" void idle();
extern "C" void movement(int x, int y);
extern "C" void passiveMotion(int x, int y);

#endif