#ifndef INITOPENGL_H
#define INITOPENGL_H

#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

class InitOpenGL {
    public:
    InitOpenGL() = default;
    
    // Initalizes a window and the viewport
    GLFWwindow* Init();

    //allows for the viewport to resize correctly
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    //allows for input to have custom action
    static void processInput(GLFWwindow* window);

    unsigned int CreateShader(const char* vertexShaderSource, const char* fragShader);

    //create 3 points for a triangle
    static float verticesTriangle[9];
    static float verticesTriangle2[9];
    static float verticesTriangleTwo[18];

    //create a rectangle from two trangles
    static float verticesRect[12];
    static unsigned int verticesRectIndices[6];
    

};

#endif