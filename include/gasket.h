#ifndef __GASKET_H__
#define __GASKET_H__

void generate_points (int npoints);
void init();
extern "C" void display();
extern "C" void keyboard(unsigned char key, int x, int y);
extern "C" void mouse(int button, int state, int x, int y);

#endif