#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

int radius = 50; // Raio inicial

void drawCircle(int centerX, int centerY, int radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(centerX + radius * cos(angle), centerY + radius * sin(angle));
    }
    glEnd();
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int centerX = (int)xpos;
        int centerY = HEIGHT - (int)ypos; // Inverter a coordenada Y

        // Desenhar circunferência com raio fixo
        drawCircle(centerX, centerY, radius);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        radius += 5; // Aumentar o raio ao pressionar a tecla para cima
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        radius = fmax(5, radius - 5); // Diminuir o raio ao pressionar a tecla para baixo, com um limite mínimo
    }
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Bresenham Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
