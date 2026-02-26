#include "../hdr/InitOpenGL.h"

GLFWwindow* InitOpenGL::Init() {
    GLFWwindow* window = nullptr;
    // Initalizes the Profile of GLFW we are using version 3.3 Core profile
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window object
    window = glfwCreateWindow(800, 600, "Learning GL", nullptr, nullptr);

    // Terminate the program if window fails
    if (!window) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return nullptr;
    }

    // Make the window the current context, of the thread?
    glfwMakeContextCurrent(window);

    // Ensure Glad which manages our function ptrs for openGL is initalized (helps makes os specfic things universal)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initalize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    // Set the size of the viewport (arg 1 and arg 2 sets the location of the lower left of the window)
    glViewport(0,0,800,600);
    return window;
}

void InitOpenGL::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void InitOpenGL::processInput(GLFWwindow* window) {
    if  (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float InitOpenGL::verticesTriangle[9] = {
        -0.5, -0.5, 0.0, //left point
        0.5, -0.5, 0.0, //right point
        0.0, 0.5, 0.0, //top point
};
