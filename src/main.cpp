/**
 * @file main.cpp
 * 
 * @author Sam Foucart sf241616@ohio.edu
 * 
 * @brief A program that uses glut and creates a window and initializes a display loop for an OpenGL program
 * 
 */
#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Angel.h"
#include "SpaceProgram.hpp"

//----------------------------------------------------------------------------
int main(int argc, char **argv)
{
  // Make sure the random number generator gets different values each
  // time the program is run.
  srand(time(NULL));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(512, 512);

  glutCreateWindow("Homework 3: Space Exploration");

  glewInit();

  cs4250::SpaceProgram spaceProgram;

  glutMainLoop();
  return EXIT_SUCCESS;
}
