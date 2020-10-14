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
namespace hw1{
const int NumPoints = 12;
const vec4 points[12] = {vec4(-1, -1, 0, 1),
                      vec4(1, -1, 0, 1),
                      vec4(1, 1, 0, 1),
                      vec4(-1, 1, 0, 1),
                      vec4(-1, -1, 0, 1),
                      vec4(1, 1, 0, 1),
                      vec4(1, 1, 1, 1),
                      vec4(-1, 1, 0, 1),
                      vec4(-1, 1, 1, 1),
                      vec4(1, 1, 1, 1),
                      vec4(1, -1, 1, 1),
                      vec4(-1, 1, 1, 1),
                     };
}
/**
 * init Initializes the shaders and calls generate_points to initialize the program
 */
void init();
extern "C" void display();
extern "C" void keyboard(unsigned char key, int x, int y);
extern "C" void mouse(int button, int state, int x, int y);
extern "C" void reshape_window(int width, int height);

#endif