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
#include <stack> 

namespace cs4250 {
extern std::stack<mat4> mvStack;
extern mat4 modelView;
extern GLuint view_loc; // location of model_view_matrix
extern GLuint color_loc;
extern GLint projection_loc;
}

/**
 * init Initializes the shaders and calls generate_points to initialize the program
 */
void init();

void drawLevel();

extern "C" void display();
extern "C" void keyboard(unsigned char key, int x, int y);
extern "C" void mouse(int button, int state, int x, int y);
extern "C" void reshape_window(int width, int height);
extern "C" void idle();
extern "C" void movement(int x, int y);
extern "C" void passiveMotion(int x, int y);

#endif