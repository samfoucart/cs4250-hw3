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
#include <memory>
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
GLuint cs4250::view_loc; // location of model_view_matrix
GLuint cs4250::color_loc; // location of model_view_matrix


extern mat4 cs4250::modelView;
std::vector<cs4250::DroneBody> drones;

//std::shared_ptr<cs4250::DroneBody> selectedDrone;
cs4250::DroneBody * selectedDrone = nullptr;

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
  cs4250::view_loc = glGetUniformLocation(program, "viewRotation");
  if (cs4250::view_loc == -1) {
    cerr << "Can't find shader variable: viewRotation!\n";
    exit(EXIT_FAILURE);
  }
  glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, RotateX(0));

  // Initialize the color uniform from vertex shader
  cs4250::color_loc = glGetUniformLocation(program, "vColor");
  if (cs4250::color_loc == -1) {
    cerr << "Can't find shader variable: vColor!\n";
    exit(EXIT_FAILURE);
  }
  glUniform4f(cs4250::color_loc, 1, 0, 0, 1);

  glClearColor(0, 0, 0, 1.0); // black background

  // Set Callbacks
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape_window);
  glutIdleFunc(idle);
  glutMotionFunc(movement);
  glutPassiveMotionFunc(passiveMotion);



  drones.push_back(cs4250::DroneBody(vec3(0, 0, 0)));
  drones.push_back(cs4250::DroneBody(vec3(1, 0, 1)));
  drones.push_back(cs4250::DroneBody(vec3(-.75, 0, -.5)));
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
    if (selectedDrone) {
      selectedDrone->fireMissle();
    }
  /*
    for(size_t i = 0; i < drones.size(); ++i) {
        drones[i].fireMissle();
  }
  */
    break;

  default:
    // Do nothing.
    break;
  }
}

extern "C" void mouse(int button, int state, int x, int y) {
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    // Calculate the position the mouse was originally clicked at to tell how much the user drags the mouse
    lastx = x;
    lasty = y;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    for (size_t i = 0; i < drones.size(); ++i) {
      if (drones[i].mouseIntersecting(x, y)) {
        drones[i].setSelected(true);
        //selectedDrone = std::make_shared<cs4250::DroneBody>(drones[i]);
        selectedDrone = &drones[i];
      } else {
        drones[i].setSelected(false);
      }
    
    }

    if (selectedDrone != nullptr) {
      if (!selectedDrone->mouseIntersecting(x, y)) {
        selectedDrone = nullptr;
      }
    }
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

  // Rotate everything down slightly and counterclockwise
  //glUniformMatrix4fv(cs4250::view_loc, 1, GL_FALSE, Scale(.5, .5, .5) * RotateX(viewTheta) * RotateY(viewPhi));
  cs4250::modelView = Scale(.25, .25, .25) * RotateX(viewTheta) * RotateY(viewPhi);

  // increment the wing angle
  wingTheta += 5;
  for(size_t i = 0; i < drones.size(); ++i) {
        drones[i].setWingTheta(wingTheta);
        drones[i].draw();
  }

  glutSwapBuffers();
}

extern "C" void movement(int x, int y) {
  // Change the viewing angle
  viewTheta = (y - lasty);
  viewPhi = (x - lastx);
}


extern "C" void passiveMotion(int x, int y){
  for (size_t i = 0; i < drones.size(); ++i) {
    if (drones[i].mouseIntersecting(x, y)) {
      drones[i].setHovered(true);
    } else {
      drones[i].setHovered(false);
    }
  }

}





