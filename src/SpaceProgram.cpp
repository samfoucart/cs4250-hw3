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
#include "SpaceProgram.hpp"
#include "Drawables/Cone.h"
#include "Drawables/Sphere.h"


using std::cerr;

// Global user variables
GLfloat viewTheta = 0; // Globals to track the position of the viewer
GLfloat viewPhi = 0;

// location the user clicks the mouse
GLsizei lastx = 250;
GLsizei lasty = 250;

// Global OpenGL Variables
GLuint buffer; // Identity of buffer object
GLuint vao;    // Identity of Vertex Array Object
GLuint loc;    // Identity of location of vPosition in shader storage
GLuint cs4250::view_loc; // location of model_view_matrix
GLuint cs4250::color_loc; // location of model_view_matrix
GLint cs4250::projection_loc;

vec4 light_position;

vec4 emmissiveColor;

GLint lightPos;
GLint emmisiveLoc;
GLint emmisiveColorLoc;

// Variables to control the amount of each light type
GLfloat ambient = 0.2;
GLfloat diffuse = 0.7;
GLfloat specular = 0.7;
GLfloat material_shininess = 5.0;
GLint emmissivep;


mat4 cs4250::modelView;
cs4250::Cone onscreenCone;
cs4250::Sphere mySphere;
std::stack<mat4> mvStack;

cs4250::SpaceProgram::SpaceProgram() {
    init();
}

// Set up shaders, etc.
void cs4250::SpaceProgram::init()
{
  // Create the points array with all the points in it.
  #ifdef __APPLE__
  glGenVertexArraysAPPLE(1, &vao);
  glBindVertexArrayAPPLE(vao);
  #else
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  #endif

  onscreenCone.cone();
  mySphere.tetrahedron(5);

  // Create and initialize a buffer object
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  /*
  glBufferData(GL_ARRAY_BUFFER,
               onscreenCone.points.size()*sizeof(vec4)
                  + onscreenCone.normals.size()*sizeof(vec3)
               , NULL, GL_STATIC_DRAW);
               */
  glBufferData(GL_ARRAY_BUFFER,mySphere.points.size()*sizeof(vec4)+ mySphere.normals.size()*sizeof(vec3), NULL, GL_STATIC_DRAW);
  //glBufferSubData(GL_ARRAY_BUFFER, 0, onscreenCone.points.size() * sizeof(vec4), onscreenCone.points[0]);
  //glBufferSubData(GL_ARRAY_BUFFER, onscreenCone.points.size() * sizeof(vec4), onscreenCone.normals.size() * sizeof(vec3), onscreenCone.normals[0]);
  glBufferSubData(GL_ARRAY_BUFFER, 0, mySphere.points.size() * sizeof(vec4), mySphere.points[0]);
  glBufferSubData(GL_ARRAY_BUFFER, mySphere.points.size() * sizeof(vec4), mySphere.normals.size() * sizeof(vec3), mySphere.normals[0]);



  // Load shaders and use the resulting shader program
  GLuint program = InitShader("../src/shaders/vshader56.glsl", "../src/shaders/fshader56.glsl");
  glUseProgram(program);

  // Initialize the vertex position attribute from the vertex shader
  loc = glGetAttribLocation(program, "vPosition");
  if (loc==-1) {
    cerr << "Can't find shader variable: vPosition!\n";
    exit(EXIT_FAILURE);
  }
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  GLint vNormal = glGetAttribLocation(program, "vNormal");
  glEnableVertexAttribArray(vNormal);
  //glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(onscreenCone.points.size()*sizeof(vec4) ));
  glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(mySphere.points.size()*sizeof(vec4) ));


    // Initialize shader lighting parameters

    // What light source is the following?
    //point4 light_position(0.0, 0.0, 1.0, 1.0);

    // What light source is the following?
    light_position=vec4(.25, .1, -2, 1.0);

    vec4 light_ambient(0.2, 0.2, 0.2, 1.0);
    vec4 light_diffuse(1.0, 1.0, 1.0, 1.0);
    vec4 light_specular(1.0, 1.0, 1.0, 1.0);

    vec4 material_ambient(1.0, 0.0, 1.0, 1.0);
    vec4 material_diffuse(1.0, 117.0 / 255.0, 24.0 / 255.0, 1.0);
    vec4 material_specular(1.0, 0.8, 0.0, 1.0);
    float  material_shininess = 5.0;
    emmissiveColor = light_diffuse;

    vec4 ambient_product = light_ambient * material_ambient;
    vec4 diffuse_product = light_diffuse * material_diffuse;
    vec4 specular_product = light_specular * material_specular;

    GLint amb=glGetUniformLocation(program, "AmbientProduct");
    glUniform4fv(amb, 1, ambient_product);

    GLint diff=glGetUniformLocation(program, "DiffuseProduct");
    glUniform4fv(diff, 1, diffuse_product);

    GLint spec=glGetUniformLocation(program, "SpecularProduct");
    glUniform4fv(spec, 1, specular_product);

    lightPos=glGetUniformLocation(program, "LightPosition");
    glUniform4fv(lightPos, 1, light_position);

    GLint shine=glGetUniformLocation(program, "Shininess");
    glUniform1f(shine, material_shininess);

    emmisiveLoc = glGetUniformLocation(program, "EmmissiveP");
    glUniform1i(emmisiveLoc, 0);

    emmisiveColorLoc = glGetUniformLocation(program, "EmmissiveColor");
    glUniform4fv(emmisiveColorLoc, 1, emmissiveColor);

    // Retrieve transformation uniform variable locations
    cs4250::view_loc = glGetUniformLocation(program, "ModelView");
    cs4250::projection_loc = glGetUniformLocation(program, "Projection");

    // Retrieve transformation uniform variable locations
    GLint SpecLoc = glGetUniformLocation(program, "Spec");
    glUniform1i(SpecLoc, spec);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 1.0, 1.0, 1.0);


  // Set Callbacks
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape_window);
  glutIdleFunc(idle);
  glutMotionFunc(movement);
  glutPassiveMotionFunc(passiveMotion);
}

void drawLevel() {

}

//----------------------------------------------------------------------------
extern "C" void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // clear the window
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

    break;  

  default:
    // Do nothing.
    break;
  }
}

extern "C" void mouse(int button, int state, int x, int y) {

}

// rehaping routine called whenever window is resized or
// moved 
extern "C" void reshape_window(int width, int height) {
    glViewport(0, 0, width, height);

    GLfloat left = -2.0, right = 2.0;
    GLfloat top = 2.0, bottom = -2.0;

    // Use following for ortho projection
    //  GLfloat zNear = -20.0, zFar = 20.0;

    // Use following for perspective projection
    GLfloat zNear = 0.2;
    GLfloat zFar = 40.0;

    GLfloat aspect = GLfloat(width)/height;

    if (aspect > 1.0) {
        left *= aspect;
        right *= aspect;
    }
    else {
        top /= aspect;
        bottom /= aspect;
    }

    mat4 projection = Perspective(45, aspect, zNear, zFar);

    // Can use either perspective or ortho projection.
    //  mat4 projection = Ortho(left, right, bottom, top, zNear, zFar);
    glUniformMatrix4fv(cs4250::projection_loc, 1, GL_TRUE, projection);
}

extern "C" void idle() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // clear the window

  glUniform1i(emmisiveLoc, 0);
  cs4250::modelView = Translate(0, 0, -.2) * Scale(.1, .1, .1);
  //onscreenCone.draw();
  //cs4250::modelView = Scale(.1, .1, .1);
  mySphere.draw();


  cs4250::modelView = Translate(light_position) * Scale(.1, .1, .1);
  glUniformMatrix4fv(cs4250::view_loc, 1, GL_TRUE, cs4250::modelView);
  glUniform1i(emmisiveLoc, 1);

  mySphere.draw();
  //onscreenCone.draw();
  //glDrawArrays(GL_TRIANGLES, 0, onscreenCone.points.size());
  glutSwapBuffers();
}

extern "C" void movement(int x, int y) {
  // Change the viewing angle
  viewTheta = (y - lasty);
  viewPhi = (x - lastx);
}


extern "C" void passiveMotion(int x, int y){
}





