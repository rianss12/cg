#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

// Defina o número de esferas
#define NUM_SPHERES 5

// Posição da lanterna
float lightPos[] = { 0.0f, 0.0f, 5.0f };

// Ângulo de rotação das esferas
float angles[NUM_SPHERES] = { 0.0f };

// Função de desenho
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Posiciona a lanterna
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Desenha as esferas girando
    for (int i = 0; i < NUM_SPHERES; ++i) {
        glPushMatrix();
        glTranslatef(2.0f * sin(angles[i]), 2.0f * cos(angles[i]), 0.0f);
        glutSolidSphere(1.0, 50, 50);
        glPopMatrix();

        angles[i] += 0.01f;
    }

    glfwSwapBuffers();
}

// Função chamada quando o tamanho da janela é alterado
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Função chamada quando o mouse é clicado
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        lightPos[0] = (float)xpos / 400.0f - 1.0f;
        lightPos[1] = 1.0f - (float)ypos / 300.0f;
    }
}

int main() {
    // Inicializa GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Configuração do contexto GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Criação da janela GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL - Esferas e Lanterna", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Torna o contexto da janela atual
    glfwMakeContextCurrent(window);

    // Inicializa GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    // Configuração do OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configura a função de callback para redimensionar a janela
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Configura a função de callback para o clique do mouse
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        drawScene();
        glfwPollEvents();
    }

    // Encerra o GLFW
    glfwTerminate();

    return 0;
}
