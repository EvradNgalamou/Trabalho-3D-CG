#ifndef _VOLUMES_H_
#define _VOLUMES_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void DrawAxes(double size);// FROM opengl3D.cpp laboratorio 4

void DrawSolideCube (double size);

void DrawSolideSphere (double radius , GLint slices , GLint stacks);

#endif
