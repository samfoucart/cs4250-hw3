/**
 * @file drone.cpp
 * 
 * @author Sam Foucart sf241616@ohio.edu
 * 
 * @brief A drone where the user can click and drag to view from different angles
 * and push space to shoot a missle
 * 
 */
// 
// Uses keyboard function for user interaction.
//
// Modified by Prof. David Chelberg to add more interactivity
// And to clean up the code and add more comments.
//
// 
#include <Angel.h>
#include "drone.h"
#include "Drawables/DroneBody.hpp"
using std::cerr;

// Global user variables
GLfloat zoomPercentage = 1.0; // Global to store zoom transformation
vec2 translation = vec2(0.0, 0.0); // Global to store translation information
GLfloat wingTheta = 0; // Global to track how much the wings have rotated
GLfloat viewTheta = 0; // Globals to track the position of the viewer
GLfloat viewPhi = 0;

// location the user clicks the mouse
GLsizei lastx = 250;
GLsizei lasty = 250; 

// Time that the missle is on screen
GLfloat missleTime = 0;
GLfloat missleTheta = 0; // angle of the missle
GLfloat misslePhi = 0;
bool missleOnScreen;


// Global OpenGL Variables
GLuint buffer; // Identity of buffer object
GLuint vao;    // Identity of Vertex Array Object
GLuint loc;    // Identity of location of vPosition in shader storage
GLuint translate_loc; // location of vertex translation matrix
GLuint rotate_loc; // location of wing rotation matrix
GLuint cs4250::view_loc; // location of model_view_matrix
GLuint scale_loc; // location of a scaling matrix

extern mat4 cs4250::modelView;
cs4250::DroneBody drone;

// Set up shaders, etc.
void init()
{
  // Create the points array with all the points in it.
  #ifdef __APPLE__
  glGenVertexArraysAPPLE(1, &vao);
  glBindVertexArrayAPPLE(vao);
  #else
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  #endif
    
  // Create and initialize a buffer object
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, NumPoints*sizeof(vec4), points, GL_STATIC_DRAW);

  // Load shaders and use the resulting shader program
  GLuint program = InitShader("../src/shaders/vshaderCube.glsl", "../src/shaders/fshaderSimple.glsl");
  glUseProgram(program);

  // Initialize the vertex position attribute from the vertex shader
  loc = glGetAttribLocation(program, "vPosition");
  if (loc==-1) {
    cerr << "Can't find shader variable: vPosition!\n";
    exit(EXIT_FAILURE);
  }
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


  // Initialize the vertex translation uniform from the vertex shader
  translate_loc = glGetUniformLocation(program, "translation");
  if (translate_loc == -1) {
    cerr << "Can't find shader variable: translation!\n";
    exit(EXIT_FAILURE);
  }
  glUniformMatrix4fv(translate_loc, 1, GL_FALSE, Translate(0, 0, 0));

  // Initialize the vertex translation uniform from the vertex shader
  scale_loc = glGetUniformLocation(program, "scaling");
  if (scale_loc == -1) {
    cerr << "Can't find shader variable: scaling!\n";
    exit(EXIT_FAILURE);
  }
  glUniformMatrix4fv(scale_loc, 1, GL_FALSE, mat4());

  // Initialize the vertex translation uniform from the vertex shader
  rotate_loc = glGetUniformLocation(program, "wingRotation");
  if (rotate_loc == -1) {
    cerr << "Can't find shader variable: wingRotation!\n";
    exit(EXIT_FAILURE);
  }
  glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, RotateX(0));

  // Initialize the vertex translation uniform from the vertex shader
  cs4250::view_loc = glGetUniformLocation(program, "viewRotation");
  if (cs4250::view_loc == -1) {
    cerr << "Can't find shader variable: viewRotation!\n";
    exit(EXIT_FAILURE);
  }
  glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, RotateX(0));

  glClearColor(0, 0, 0, 1.0); // black background

  // Set Callbacks
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape_window);
  glutIdleFunc(idle);
  glutMotionFunc(movement);
}

//----------------------------------------------------------------------------
extern "C" void display() {
  glClear(GL_COLOR_BUFFER_BIT);          // clear the window
  glutSwapBuffers();
}

//----------------------------------------------------------------------------
// Callback to process normal keyboard characters entered.
// 
extern "C" void keyboard(unsigned char key, int x, int y) {
  switch (key) {

    // Escape key (quit)
  case 033:
  case 'Q':
  case 'q':
    exit(EXIT_SUCCESS);
    break;

  case ' ':
    // When the user pushes space, shoot a missle
    missleOnScreen = true;
    missleTime = 0;
    missleTheta = viewTheta;
    misslePhi = viewPhi;
    break;

  default:
    // Do nothing.
    break;
  }
}

extern "C" void mouse(int button, int state, int x, int y) {
  if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    // Calculate the position the mouse was originally clicked at to tell how much the user drags the mouse
    lastx = x;
    lasty = y;
  }
}

// rehaping routine called whenever window is resized or
// moved 
extern "C" void reshape_window(int width, int height) {
  // adjust viewport and clear
  glViewport(0, 0, width, height);

  glClearColor (0.0, 0.0, 0.0, 1.0);

  //glUniform2f(windowSizeLoc, width, height);             // Pass the window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glFlush();
}

extern "C" void idle() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // clear the window

  // increment the wing angle
  wingTheta += 5;
  drone.setWingTheta(wingTheta);

  // Rotate everything down slightly and counterclockwise
  //glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, Scale(.5, .5, .5) * RotateX(viewTheta) * RotateY(viewPhi));
  cs4250::modelView = Scale(.5, .5, .5) * RotateX(viewTheta) * RotateY(viewPhi);
  
  // draw drone body
  
  glUniformMatrix4fv(scale_loc, 1, GL_FALSE, mat4());
  glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, RotateX(0));
  // make the center lines not translated
  glUniformMatrix4fv(translate_loc, 1, GL_TRUE, Translate(0, 0, 0));
  drone.draw();
  //glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines

  //drawRotors();
  drawLauncher();
  drawMissle();

  glutSwapBuffers();
}

extern "C" void movement(int x, int y) {
  // Change the viewing angle
  viewTheta = (y - lasty);
  viewPhi = (x - lastx);
}

void drawRotors() {
  // Shape the wing
  glUniformMatrix4fv(scale_loc, 1, GL_FALSE, Scale(.2, .05, .1));
  // Rotate the wing
  glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, RotateY(wingTheta));
  // translate each wing
  glUniformMatrix4fv(translate_loc, 1, GL_TRUE, Translate(.25, .25, .5));
  glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines

  glUniformMatrix4fv(scale_loc, 1, GL_FALSE, Scale(.2, .05, .1));
  glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, RotateY(wingTheta));
  // translate each wing
  glUniformMatrix4fv(translate_loc, 1, GL_TRUE, Translate(-.25, .25, .5));
  glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines

  glUniformMatrix4fv(scale_loc, 1, GL_FALSE, Scale(.2, .05, .1));
  glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, RotateY(wingTheta));
  // translate each wing
  glUniformMatrix4fv(translate_loc, 1, GL_TRUE, Translate(-.25, .25, -.5));
  glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines

  glUniformMatrix4fv(scale_loc, 1, GL_FALSE, Scale(.2, .05, .1));
  glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, RotateY(wingTheta));
  // translate each wing
  glUniformMatrix4fv(translate_loc, 1, GL_TRUE, Translate(.25, .25, -.5));
  glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines
}

void drawMissle() {

  if (missleOnScreen) {
    // rotate the missle towards the constant trajectory
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, Scale(.5, .5, .5) * RotateX(missleTheta) * RotateY(misslePhi));

    // Shape the missle
    glUniformMatrix4fv(scale_loc, 1, GL_FALSE, Scale(.01, .01, .3));
    // Make sure the missle doesn't rotate with the wings
    glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, RotateY(0));
    // translate each wing
    glUniformMatrix4fv(translate_loc, 1, GL_TRUE, Translate(0, -.25, .5 + missleTime));
    glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines

    // Rotate everything back to normal
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, Scale(.5, .5, .5) * RotateX(viewTheta) * RotateY(viewPhi));
    // tell if missle is on screen
    if (missleTime > 5) {
      missleOnScreen = false;
    } else {
      missleTime += .1;
    }
  }
  
}

void drawLauncher() {
  // Shape the launcher
  glUniformMatrix4fv(scale_loc, 1, GL_FALSE, Scale(.01, .01, .3));
  // make sure the launcher doesn't rotate with the wings
  glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, RotateY(0));
  // translate each wing
  glUniformMatrix4fv(translate_loc, 1, GL_TRUE, Translate(0, -.25, .5));
  glDrawArrays(GL_LINE_STRIP, 0, NumPoints); // draw the lines
}

