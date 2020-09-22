#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Angel.h"
#include "gasket.h"

//----------------------------------------------------------------------------
int main(int argc, char **argv)
{
  // Make sure the random number generator gets different values each
  // time the program is run.
  srand(time(NULL));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
  glutInitWindowSize(512, 512);

  glutCreateWindow("Homework 0: Modified Sierpinski Gasket");

  glewInit();

  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutMainLoop();
  return EXIT_SUCCESS;
}
