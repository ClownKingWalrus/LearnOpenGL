//sql connector hdrs
#include "../hdr/Utils.h"
#include "../hdr/InitOpenGL.h"
#include "../hdr/Shader.h"
#include <cmath>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n" //specify output color for frag shader
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n" //output is darkred
"}\0";

const char* fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0"; 

// Frag shader for color changing (uniform is a global var we can get in runtime)
const char* fragShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"FragColor = ourColor;\n"
"}\0";

// Shader for multi colord triangle
const char* vertexShaderSourceMultiColor = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" //position args first 3 floats
"layout (location = 1) in vec3 aColor;\n" //color args second 3 floats
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"}\n";

const char* fragShaderSourceMultiColor = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(ourColor, 1.0);\n"
"}\0"; 

int main() {
    InitOpenGL initGL;
    GLFWwindow* window = initGL.Init();
    if (!window) {
        return -1;
    }
    // Register our Viewport resizer
    glfwSetFramebufferSizeCallback(window, InitOpenGL::framebuffer_size_callback);

    //create Shader programs
    // unsigned int shaderProgram = initGL.CreateShader(vertexShaderSource, fragShaderSource);
    // unsigned int shaderProgram2 = initGL.CreateShader(vertexShaderSource, fragShaderSource2);
    // unsigned int shaderProgram3 = initGL.CreateShader(vertexShaderSourceMultiColor, fragShaderSourceMultiColor);
    Shader ourShader("shaders/shaderVertex.txt", "shaders/shaderFragment.txt");
    std::cerr << "test\n";



    // Create VAO or vertex arrary object and Vertex Buffer Object
    unsigned int VAO, VBO, VAO2, VBO2, VBO3, VAO3, EBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);

    // glGenVertexArrays(1, &VAO2);
    // glGenBuffers(1, &VBO2);

    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);
    
    glGenBuffers(1, &EBO);

    //bind vertex array object then set vertex buffer
    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(InitOpenGL::verticesTriangle), InitOpenGL::verticesTriangle, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 * sizeof(float)), (void*)0);
    // glEnableVertexAttribArray(0);

    // //glBufferData(GL_ARRAY_BUFFER, sizeof(InitOpenGL::verticesRect), InitOpenGL::verticesRect, GL_STATIC_DRAW);

    // //bind vertex array object then set vertex buffer
    // glBindVertexArray(VAO2);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(InitOpenGL::verticesTriangle2), InitOpenGL::verticesTriangle2, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 * sizeof(float)), (void*)0);
    // glEnableVertexAttribArray(0);

    // Multi color Triangle VBO
    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(InitOpenGL::verticesTriangle3FullPrismo), InitOpenGL::verticesTriangle3FullPrismo, GL_STATIC_DRAW);
    // Position Atrribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (void*)0);
    glEnableVertexAttribArray(0);
    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (void*) (3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    
    // Put our unqiue points into the Element Buffer
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(InitOpenGL::verticesRectIndices), InitOpenGL::verticesRectIndices, GL_STATIC_DRAW);
    
    // WireFrame mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Keep drawing the window until we close it (prevents from opening for 1 frame and closing after completion)
    while (!glfwWindowShouldClose(window)) {
        // Clear the previous buffers color, so we dont see it this frame (Uses the state from clear Color)
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //////////////// Rendering Commands here ////////////////
        // // Draw Triangle
        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glUseProgram(shaderProgram2);
        // glDrawArrays(GL_TRIANGLES, 3, 3);

        // Shader gradient change overtime
        // float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue) / 2.0f) + 0.5;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
        // glUseProgram(shaderProgram2);
        // glUniform4f(vertexColorLocation, 0.0, greenValue, 0.0, 1.0);

        // Gradient Triangle
        ourShader.use();
        //ourShader.setFloat("someUniform", 1.0f);
        glBindVertexArray(VAO3);


        //draw triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glBindVertexArray(0);
        //////////////// ^^^ Rendering Commands ^^^ ////////////////
        
        // Swaps Buffers swaps the color buffer (prevents artifcats of seeing a buffer being drawn by creating 2 buffers and only showing the finished buffer as the final product, 1 still buffer to placehold while the other loads the next image)
        glfwSwapBuffers(window);
        // Poll events checks if any events happen like keyboard inputs
        glfwPollEvents(); 

        // Take action on input press
        InitOpenGL::processInput(window);
    }

    // Close the application cleanly
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteVertexArrays(1, &VAO2);
    // glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO3);
    glDeleteBuffers(1, &VBO3);
    //glDeleteProgram(shaderProgram);
    //glDeleteProgram(shaderProgram2);
    //glDeleteProgram(shaderProgram3);

    glfwTerminate();
    return 0;
}