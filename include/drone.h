/**
 * @file gasket.h
 * 
 * @author Sam Foucart sf241616@ohio.edu
 * 
 * @brief A modified version of Angel, Shreiner, Chelberg's sierpinski gasket program.
 * The modification changes the color and implements panning and zooming.
 * 
 */
#ifndef __GASKET_H__
#define __GASKET_H__

#include <Angel.h>
const int NumPoints = 22;
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

void drawRotors();
void drawMissle();
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