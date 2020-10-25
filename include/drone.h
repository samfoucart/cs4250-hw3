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

extern std::stack<mat4> mvStack;
extern mat4 modelView;

/**
 * Number of points used to draw a wireframe cube with GL_LINE_STRIP
 */ 
const int NumPoints = 22;

/**
 * Points used to draw a wireframe cube with GL_LINE_STRIP
 */ 
const vec4 points[22] = {
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
                     };

/**
 * Draws the rotated rotors of the drone
 */ 
void drawRotors();

/**
 * Draws the missle that moves compared to time
 */ 
void drawMissle();

/**
 * Draws the launcher that the missle comes from
 */ 
void drawLauncher();

/**
 * init Initializes the shaders and calls generate_points to initialize the program
 */
void init();
extern "C" void display();
extern "C" void keyboard(unsigned char key, int x, int y);
extern "C" void mouse(int button, int state, int x, int y);
extern "C" void reshape_window(int width, int height);
extern "C" void idle();
extern "C" void movement(int x, int y);

#endif