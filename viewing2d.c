#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat xOffset = -100.0f;
GLfloat yOffset = 0.0f;

GLfloat xStep = 1.0f;
GLfloat yStep = 0.5f;

void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glVertex2i(50, -50);
    glVertex2i(0, 50);
    glVertex2i(-50, -50);
    glEnd();
}

void drawSquareOutline() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(-100, 100);
    glVertex2i(100, 100);
    glVertex2i(100, -100);
    glVertex2i(-100, -100);
    glEnd();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void timerFunc(int value) {
    if (xOffset > 100 || xOffset < -300)
        xStep = -xStep;

    xOffset += xStep;

    if (yOffset > 150 || yOffset < 0)
        yStep = -yStep;

    yOffset += yStep;

    glutPostRedisplay();
    glutTimerFunc(10, timerFunc, 1);
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(0, 300, 300, 300);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawTriangle();

    glLoadIdentity();
    gluOrtho2D(xOffset, xOffset + 200.0f, -100.0f, 100.0f);
    glViewport(300, 300, 300, 300);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawTriangle();

    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, yOffset, yOffset + 200.0f);
    glViewport(0, 0, 300, 300);
    glColor3f(0.0f, 0.0f, 1.0f);
    drawTriangle();

    glLoadIdentity();
    gluOrtho2D(-yOffset, yOffset, -yOffset, yOffset);
    glViewport(300, 0, 300, 300);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawTriangle();

    glLoadIdentity();

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Modified 2D View");
    glutDisplayFunc(displayFunc);
    glutTimerFunc(10, timerFunc, 1);
    init();
    glutMainLoop();
    return 0;
}
