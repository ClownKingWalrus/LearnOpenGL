//sql connector hdrs
#include "../hdr/Utils.h"
#include "../hdr/InitOpenGL.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0"; 


int main() {
    InitOpenGL initGL;
    GLFWwindow* window = initGL.Init();
    if (!window) {
        return -1;
    }
    // Register our Viewport resizer
    glfwSetFramebufferSizeCallback(window, InitOpenGL::framebuffer_size_callback);

    // Create Shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //attach shader source to shader object then compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check for compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }

    // Create Frag Shader object
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, nullptr);
    glCompileShader(fragShader);

    // Check for compile errors
    int successfrag;
    char infoLogfrag[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &successfrag);

    if (!successfrag) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLogfrag);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" <<
        infoLogfrag << std::endl;
    }

    // Create Shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    // Check for compile errors
    int successShaderProgram;
    char infoLogShaderProgram[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successShaderProgram);

    if (!successShaderProgram) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogShaderProgram);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" <<
        infoLogShaderProgram << std::endl;
    }
    // Ensure all shader and render calls use this shader program
    glUseProgram(shaderProgram);

    // Delete old shaders as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    // Tell opengl how to process our points
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 * sizeof(float)), (void*)0);
    glEnableVertexAttribArray(0);

    // Create VAO or vertex arrary object and Vertex Buffer Object
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //copy vertex array in the buffer
        // Create Vertex buffer Object
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(InitOpenGL::verticesTriangle), InitOpenGL::verticesTriangle, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
    (void*)0);
    glEnableVertexAttribArray(0);

    // Draw Our Object
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // Keep drawing the window until we close it (prevents from opening for 1 frame and closing after completion)
    while (!glfwWindowShouldClose(window)) {
        // Clear the previous buffers color, so we dont see it this frame (Uses the state from clear Color)
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        // Swaps Buffers swaps the color buffer (prevents artifcats of seeing a buffer being drawn by creating 2 buffers and only showing the finished buffer as the final product, 1 still buffer to placehold while the other loads the next image)
        glfwSwapBuffers(window);
        // Poll events checks if any events happen like keyboard inputs
        glfwPollEvents(); 

        // Take action on input press
        InitOpenGL::processInput(window);

        //////////////// Rendering Commands here ////////////////
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    // Close the application cleanly
    glfwTerminate();
    return 0;
}