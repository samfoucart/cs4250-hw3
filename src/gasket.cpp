// Two-Dimensional Sierpinski Gasket       
// Generated using randomly selected vertices and bisection
// 
// Uses keyboard function for user interaction.
//
// Modified by Prof. David Chelberg to add more interactivity
// And to clean up the code and add more comments.
//
// last-modified: Tue Sep 15 15:21:54 2020
// 
#include <Angel.h>
using std::cerr;

// Global user variables
int NumPoints = 1000;  // Global to hold how many points we want to generate
vec2 *points;          // Global to hold the generated points
		       // (dynamically allocated).
GLfloat zoomPercentage = 1.0;


// Global OpenGL Variables
GLuint buffer; // Identity of buffer object
GLuint vao;    // Identity of Vertex Array Object
GLuint loc;    // Identity of location of vPosition in shader storage
GLuint zoom;

//----------------------------------------------------------------------------
// Start with a triangle.  Pick any point inside the triangle, and
// find the point halfway towards any vertex (draw this point), and
// repeat with this new point as the point inside the triangle until
// you have sufficient points.
//
void generate_points (int npoints)
{
  points = new vec2[npoints];
  // Specifiy the vertices for a triangle
  vec2 vertices[3] = {vec2(-1.0, -1.0), 
		      vec2( 0.0,  1.0), 
		      vec2( 1.0, -1.0)};

  // Select an arbitrary initial point inside of the triangle
  points[0] = vec2(0.25, 0.50);

  // compute and store N-1 new points
  for (int i = 1; i < npoints; ++i) {
    int j = rand() % 3;   // pick a vertex at random

    // Compute the point halfway between the selected vertex
    //   and the previous point
    points[i] = (points[i - 1] + vertices[j]) / 2.0;
  }
}

// Set up shaders, etc.
void init()
{
  // Create the points array with all the points in it.
  generate_points(NumPoints);

  // Create a vertex array object
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
    
  // Create and initialize a buffer object
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, NumPoints*sizeof(vec2), points, GL_STATIC_DRAW);

  // Load shaders and use the resulting shader program
  GLuint program = InitShader("src/shaders/vshaderSimple.glsl", "src/shaders/fshader21.glsl");
  glUseProgram(program);

  // Initialize the vertex position attribute from the vertex shader
  loc = glGetAttribLocation(program, "vPosition");
  if (loc==-1) {
    cerr << "Can't find shader variable: vPosition!\n";
    exit(EXIT_FAILURE);
  }
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  zoom = glGetUniformLocation(program, "zoomPercentage");
  if (zoom==-1) {
    cerr << "Can't find shader variable: zoomPercentage!\n";
    exit(EXIT_FAILURE);
  }
  glUniform1f(zoom, zoomPercentage);

  glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

//----------------------------------------------------------------------------
extern "C" void display()
{
  glClear(GL_COLOR_BUFFER_BIT);          // clear the window
  //glEnable(GL_PROGRAM_POINT_SIZE_EXT);
  //glPointSize(5);
  glDrawArrays(GL_POINTS, 0, NumPoints); // draw the points
  glutSwapBuffers();
}

//----------------------------------------------------------------------------
// Callback to process normal keyboard characters entered.
// 
extern "C" void keyboard(unsigned char key, int x, int y)
{

  switch (key) {

  case 'h':
    // Help -- give instructions
    std::cout << "Commands are p/P for point size, +/- for number of points" << std::endl;
    break;

    // Escape key (quit)
  case 033:
  case 'Q':
  case 'q':
    exit(EXIT_SUCCESS);
    break;

  case 'p':
    // Make points small
    // The next lines may make the code draw faster
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_BLEND);
    glPointSize(1.0);
    glutPostRedisplay();
    break;
  case 'P':
    // Make points big
    glEnable(GL_POINT_SMOOTH);
    // In order to enable antialiasing, we need the following two lines
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(2.0);
    glutPostRedisplay();
    break;

  case '+':
    // Increase number of points.
    NumPoints*=2;
    // Let the user know how many points are being displayed
    std::cout << "NumPoints = " << NumPoints << std::endl;
    // Reclaim memory for current points array
    delete points;
    generate_points(NumPoints);

    // Send the new points to the GPU
    // Next line isn't necessary, but doesn't hurt anything either.
    //    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBufferData(GL_ARRAY_BUFFER, NumPoints*sizeof(vec2), points, GL_STATIC_DRAW);      
    glutPostRedisplay();

    break;
  case '-':
    // Decrease number of points.
    NumPoints/=2;
    // Be sure we don't go to 0.
    if (NumPoints <1){
      NumPoints=1;
    }
    // Let the user know how many points are being displayed
    std::cout << "NumPoints = " << NumPoints << std::endl;
    // Reclaim memory for current points array
    delete points;
    generate_points(NumPoints);

    // Send the new points to the GPU
    //    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBufferData(GL_ARRAY_BUFFER, NumPoints*sizeof(vec2), points, GL_STATIC_DRAW);      
    glutPostRedisplay();

    break;

  case ' ':
    // Increase zoom percentage
    zoomPercentage += .1;
    // Let the user know the zoom percentage
    std::cout << "Zoom Percentage: " << zoomPercentage << std::endl;
    // Send the new value to the GPU
    glUniform1f(zoom, zoomPercentage);
    glutPostRedisplay();
    break;

  case 'b':
  case 'B':
    // Increase zoom percentage
    zoomPercentage -= .1;
    // Let the user know the zoom percentage
    std::cout << "Zoom Percentage: " << zoomPercentage << std::endl;
    // Send the new value to the GPU
    glUniform1f(zoom, zoomPercentage);
    glutPostRedisplay();
  break;      

  default:
    // Do nothing.
    break;
  }
}

