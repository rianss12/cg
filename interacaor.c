#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592654

float translateY = 0.0;
float translateX = 0.0;
float rotationAngle = 0.0;

void printMatrix() {
  float matrix[16];
  int i, j;

  printf("\n\nMatrix M = \n");
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      printf("%f ", matrix[i + j * 4]);
    }
    printf("\n");
  }
  printf("\n");
}

void drawCircle() {
  int i;
  float angle = 0.0;
  glBegin(GL_POLYGON);
  for (i = 0; i <= 10; i++) {
    angle = 2 * PI * i / 10.0;
    glVertex2f(0.25 * cos(angle) + translateX, 0.25 * sin(angle) + translateY);
  }
  glEnd();
}

void drawSquare() {
  glBegin(GL_POLYGON);
  glVertex2f(-0.25 + translateX, 0.25 + translateY);
  glVertex2f(0.25 + translateX, 0.25 + translateY);
  glVertex2f(0.25 + translateX, -0.25 + translateY);
  glVertex2f(-0.25 + translateX, -0.25 + translateY);
  glEnd();
}

void display() {
  glClearColor(0, 0, 0, 0); // Black
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  printMatrix();

  glColor3f(1.0, 1.0, 1.0);
  drawCircle();

  glFlush();
}

void specialKeys(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    translateY += 0.05;
    break;
  case GLUT_KEY_DOWN:
    translateY -= 0.05;
    break;
  case GLUT_KEY_RIGHT:
    translateX += 0.05;
    break;
  case GLUT_KEY_LEFT:
    translateX -= 0.05;
    break;

  default:
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Modified OpenGL Program");
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
  glutMainLoop();
  return 0;
}
