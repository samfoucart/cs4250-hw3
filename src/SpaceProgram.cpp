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
#include "Drawables/Cylinder.h"
#include "Drawables/SpaceShip.h"
#include "Drawables/Asteroid.h"


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


mat4 cs4250::SpaceProgram::modelView;
//cs4250::Cone onscreenCone;
//cs4250::Sphere mySphere;
std::stack<mat4> cs4250::SpaceProgram::mvStack;
std::vector<std::unique_ptr<cs4250::Drawable>> cs4250::SpaceProgram::drawables;
std::vector<vec4> cs4250::SpaceProgram::allPoints;
std::vector<vec3> cs4250::SpaceProgram::allNormals;
GLint cs4250::SpaceProgram::bufferSize;
int cs4250::SpaceProgram::spaceShipIndex;
vec4 cs4250::SpaceProgram::cameraPosition;
GLfloat cs4250::SpaceProgram::cameraPitch;
GLfloat cs4250::SpaceProgram::cameraYaw;
GLfloat cs4250::SpaceProgram::cameraRoll;
vec4 cs4250::SpaceProgram::lightPosition;
vec4 cs4250::SpaceProgram::defaultLightPos;
GLint cs4250::SpaceProgram::lightLocation;

cs4250::SpaceProgram::SpaceProgram() {
    defaultLightPos = vec4(0, 5, 10, 0);
    SpaceProgram::bufferSize = 0;
    SpaceProgram::init();
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

  createLevel();

    // Create and initialize a buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER,allPoints.size()*sizeof(vec4)+ allNormals.size()*sizeof(vec3), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, allPoints.size() * sizeof(vec4), allPoints[0]);
    glBufferSubData(GL_ARRAY_BUFFER, allPoints.size() * sizeof(vec4), allNormals.size() * sizeof(vec3), allNormals[0]);



  // Load shaders and use the resulting shader program
  GLuint program = InitShader("../src/shaders/vshader53.glsl", "../src/shaders/fshader53.glsl");
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
  glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(allPoints.size() * sizeof(vec4)));


    // Initialize shader lighting parameters

    // What light source is the following?
    //point4 light_position(0.0, 0.0, 1.0, 1.0);

    // What light source is the following?
    lightPosition = defaultLightPos;

    vec4 light_ambient(0.2, 0.2, 0.2, 1.0);
    vec4 light_diffuse(1.0, 1.0, 1.0, 1.0);
    vec4 light_specular(1.0, 1.0, 1.0, 1.0);

    vec4 material_ambient(1.0, 0.0, 1.0, 1.0);
    vec4 material_diffuse(.34, .33, .33, 1.0);
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

    lightLocation = glGetUniformLocation(program, "LightPosition");
    glUniform4fv(lightLocation, 1, lightPosition);

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

    glClearColor(.21, .175, .175, 1.0);


  // Set Callbacks
  glutDisplayFunc(cs4250::SpaceProgram::display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape_window);
  glutIdleFunc(idle);
  glutMotionFunc(movement);
  glutPassiveMotionFunc(passiveMotion);
}

void cs4250::SpaceProgram::createLevel() {

    Sphere first(4);
    allPoints = first.points;
    allNormals = first.normals;
    first.transformation = Translate(.5, .5, -10);
    drawables.push_back(std::make_unique<Sphere>(first));

    /*
    Asteroid asteroid1(4);
    asteroid1.bufferPosition = allPoints.size();
    allPoints.insert(allPoints.end(), asteroid1.points.begin(), asteroid1.points.end());
    allNormals.insert(allNormals.end(), asteroid1.normals.begin(), asteroid1.normals.end());
    asteroid1.transformation = Translate(-1, .5, 5);
    drawables.push_back(std::make_unique<Asteroid>(asteroid1));
     */



    allPoints = first.points;
    allNormals = first.normals;
    first.transformation = Translate(.5, .5, -10);
    drawables.push_back(std::make_unique<Sphere>(first));


    Cone second;
    second.bufferPosition = allPoints.size();
    second.transformation = Translate(-.5, -.5, -15);
    allPoints.insert(allPoints.end(), second.points.begin(), second.points.end());
    allNormals.insert(allNormals.end(), second.normals.begin(), second.normals.end());
    drawables.push_back(std::make_unique<Cone>(second));


    for (int i = 0; i < (rand() % 20) + 100; ++i) {
        Sphere asteroid = Sphere(1);
        asteroid.bufferPosition = allPoints.size();
        asteroid.velocity = vec3((rand() % 5) - 2, (rand() % 5) - 2, (rand() % 5) - 2);
        asteroid.position = vec3((rand() % 100) - 50, (rand() % 100) - 50, (rand() % 100) - 50);
        asteroid.transformation = Scale((float) (rand() % 20) / 10, (float) (rand() % 20) / 10, (float) (rand() % 20) / 10);
        drawables.push_back(std::make_unique<Sphere>(asteroid));
        allPoints.insert(allPoints.end(), asteroid.points.begin(), asteroid.points.end());
        allNormals.insert(allNormals.end(), asteroid.normals.begin(), asteroid.normals.end());
    }

    for (int i = 0; i < (rand() % 20) + 20; ++i) {
        Sphere planet = Sphere(5);
        planet.bufferPosition = allPoints.size();
        //asteroid.velocity = vec3((rand() % 10) - 5, (rand() % 10) - 5, (rand() % 10) - 5);
        planet.position = vec3((rand() % 250) - 125, (rand() % 250) - 100, (rand() % 250) - 125);
        planet.transformation = Scale((rand() % 15) + 5, (rand() % 15) + 5, (rand() % 15) + 5);
        drawables.push_back(std::make_unique<Sphere>(planet));
        allPoints.insert(allPoints.end(), planet.points.begin(), planet.points.end());
        allNormals.insert(allNormals.end(), planet.normals.begin(), planet.normals.end());
    }


    Sphere third(1);
    third.bufferPosition = allPoints.size();
    third.velocity = vec3(0, 0, 0);
    third.transformation = Translate(5, .5, -20);
    drawables.push_back(std::make_unique<Sphere>(third));
    allPoints.insert(allPoints.end(), third.points.begin(), third.points.end());
    allNormals.insert(allNormals.end(), third.normals.begin(), third.normals.end());



    Cylinder fifth;
    fifth.bufferPosition = allPoints.size();
    allPoints.insert(allPoints.end(), fifth.points.begin(), fifth.points.end());
    allNormals.insert(allNormals.end(), fifth.normals.begin(), fifth.normals.end());
    fifth.transformation = Translate(0, -1, -20) * Scale(.5, .5, .5);
    drawables.push_back(std::make_unique<Cylinder>(fifth));



    Cube fourth;
    fourth.bufferPosition = allPoints.size();
    fourth.colorcube();
    fourth.transformation = Translate(0, 5, 0);
    drawables.push_back(std::make_unique<Cube>(fourth));
    allPoints.insert(allPoints.end(), fourth.points.begin(), fourth.points.end());
    allNormals.insert(allNormals.end(), fourth.normals.begin(), fourth.normals.end());





    SpaceShip spaceShip = SpaceShip(allPoints.size());
    std::vector<vec4> spaceShipPoints = spaceShip.getAllPoints();
    allPoints.insert(allPoints.end(), spaceShipPoints.begin(), spaceShipPoints.end());
    std::vector<vec3> spaceShipNormals = spaceShip.getAllNormals();
    allNormals.insert(allNormals.end(), spaceShipNormals.begin(), spaceShipNormals.end());
    drawables.push_back(std::make_unique<SpaceShip>(spaceShip));
    spaceShipIndex = drawables.size() - 1;

    for (int i = 0; i < (rand() % 5) + 1; ++i) {
        SpaceShip listSpaceShip = SpaceShip(allPoints.size());
        spaceShipPoints = listSpaceShip.getAllPoints();
        allPoints.insert(allPoints.end(), spaceShipPoints.begin(), spaceShipPoints.end());
        spaceShipNormals = listSpaceShip.getAllNormals();
        allNormals.insert(allNormals.end(), spaceShipNormals.begin(), spaceShipNormals.end());
        listSpaceShip.velocity = vec3((rand() % 5) - 2, (rand() % 5) - 2, (rand() % 5) - 2);
        listSpaceShip.position = vec3((rand() % 50) - 25, (rand() % 25) - 5, (rand() % 50) - 25);
        drawables.push_back(std::make_unique<SpaceShip>(listSpaceShip));
    }

    cameraPosition = vec4(0, 0, 0, 1);
    cameraPitch = 0;
    cameraYaw = 0;
    cameraRoll = 0;
    modelView = Translate(cameraPosition) * RotateZ(cameraPitch);

}

void cs4250::SpaceProgram::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // clear the window
    glUniform1i(emmisiveLoc, 0);
    //cs4250::SpaceProgram::modelView = Translate(0, 0, -10);
    cs4250::SpaceProgram::modelView = Translate(0, -3, -10)
                                      * RotateX(cs4250::SpaceProgram::cameraPitch)
                                      * RotateY(cs4250::SpaceProgram::cameraYaw)
                                      * Translate(cs4250::SpaceProgram::cameraPosition);
    glUniformMatrix4fv(cs4250::view_loc, 1, GL_TRUE, cs4250::SpaceProgram::modelView);
    for (auto & drawable : cs4250::SpaceProgram::drawables) {
        if (drawable != nullptr) {
            drawable->draw();
        }
    }
    glutSwapBuffers();
}

/*

//----------------------------------------------------------------------------
extern "C" void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // clear the window
  glutSwapBuffers();
}
 */

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
      cs4250::SpaceProgram::drawables[cs4250::SpaceProgram::spaceShipIndex]->pitchUp();
      cs4250::SpaceProgram::cameraPitch -= 15;
      break;

  case 's':
      cs4250::SpaceProgram::drawables[cs4250::SpaceProgram::spaceShipIndex]->pitchDown();
      cs4250::SpaceProgram::cameraPitch += 15;
      break;

  case 'a':
      cs4250::SpaceProgram::drawables[cs4250::SpaceProgram::spaceShipIndex]->turnLeft();
      cs4250::SpaceProgram::cameraYaw -= 15;
      break;

  case 'd':
      cs4250::SpaceProgram::drawables[cs4250::SpaceProgram::spaceShipIndex]->turnRight();
      cs4250::SpaceProgram::cameraYaw += 15;
      break;

  case 'w':
      cs4250::SpaceProgram::drawables[cs4250::SpaceProgram::spaceShipIndex]->moveForward();
      cs4250::SpaceProgram::cameraPosition = Translate(RotateY(- cs4250::SpaceProgram::cameraYaw) * RotateX(- cs4250::SpaceProgram::cameraPitch) * vec4(0, 0, 1, 1)) * cs4250::SpaceProgram::cameraPosition;
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
    GLfloat zNear = .2;
    GLfloat zFar = 1000.0;

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
    static int last_time = glutGet(GLUT_ELAPSED_TIME);

    int delta_time = glutGet(GLUT_ELAPSED_TIME) - last_time;
    last_time = glutGet(GLUT_ELAPSED_TIME);
    for (auto & drawable : cs4250::SpaceProgram::drawables) {
        if (drawable != nullptr) {
            drawable->update(delta_time);
        }
    }
  glutPostRedisplay();
}

extern "C" void movement(int x, int y) {
  // Change the viewing angle
  viewTheta = (y - lasty);
  viewPhi = (x - lastx);
}


extern "C" void passiveMotion(int x, int y){
}





