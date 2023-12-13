#include <GL/glut.h>
#include <math.h>

void desenhaCirculo(float raio, float corR, float corG, float corB, float posX, float posY) {
    int i;
    int triangulos = 100;
    glColor3f(corR, corG, corB);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX, posY);
    for (i = 0; i <= triangulos; i++) {
        float theta = (2.0f * M_PI) * ((float)i / (float)triangulos);
        float x = raio * cosf(theta);
        float y = raio * sinf(theta);
        glVertex2f(x + posX, y + posY);
    }
    glEnd();
}

void desenhaTriangulo(float x1, float y1, float x2, float y2, float x3, float y3, float corR, float corG, float corB) {
    glColor3f(corR, corG, corB);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void desenhaPalhaco() {
    // Cabeça
    desenhaCirculo(20, 1.0, 1.0, 0.0, 0, 0);

    // Olhos
    desenhaCirculo(2, 0.0, 0.0, 0.0, -8, 5);
    desenhaCirculo(2, 0.0, 0.0, 0.0, 8, 5);

    // Nariz
    desenhaTriangulo(0, 0, -2, -5, 2, -5, 1.0, 0.5, 0.5);

    // Boca
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-5, -5);
    glVertex2f(-2, -8);
    glVertex2f(2, -8);
    glVertex2f(5, -5);
    glEnd();
    glLineWidth(1);
}

void desenhaCatavento() {
    // Haste
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(0, -80);
    glVertex2f(0, 80);
    glEnd();
    glLineWidth(1);

    // Pás
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 80);
    glVertex2f(20, 120);
    glVertex2f(-20, 120);

    glVertex2f(0, 80);
    glVertex2f(20, 40);
    glVertex2f(-20, 40);

    glVertex2f(0, 80);
    glVertex2f(120, 20);
    glVertex2f(120, -20);

    glVertex2f(0, 80);
    glVertex2f(40, 20);
    glVertex2f(40, -20);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenha o palhaço
    glPushMatrix();
    glTranslatef(-50, 0, 0);
    desenhaPalhaco();
    glPopMatrix();

    // Desenha o catavento
    glPushMatrix();
    glTranslatef(50, 0, 0);
    glRotatef(45, 0, 0, 1);
    desenhaCatavento();
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Palhaco e Catavento");

    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return 0;
}
