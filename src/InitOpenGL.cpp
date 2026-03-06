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

unsigned int InitOpenGL::CreateShader(const char* vertexShaderSource, const char* fragShaderSource) {
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
    
    // Delete old shaders as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    return shaderProgram;
}

//XYZ where Z is depth
float InitOpenGL::verticesTriangle[9] = {
        -1, -0.5, 0.0, //left point
        0.0, -0.5, 0.0, //right point
        -0.5, 0.5, 0.0, //top point
};

float InitOpenGL::verticesTriangle2[9] = {
        //triangle 2 Shift Right
        0.0, 0.5, 0.0, //left point
        1.0, 0.5, 0.0, //right point
        0.5, -0.5, 0.0, //top point
};

float InitOpenGL::verticesTriangle3FullPrismo[18] = {
        //Triangle full prismo
        //XYZ : RGB
        0.5, -0.5, 0.0, 1.0, 0.0, 0.0, //bottom Right
        -0.5, -0.5, 0.0, 0.0, 1.0, 0.0, //bot left
        0.0, 0.5, 0.0, 0.0, 0.0, 1.0, //top middle
};

float InitOpenGL::verticesTriangleTwo[18] = {
        -1, -0.5, 0.0, //left point
        0.0, -0.5, 0.0, //right point
        -0.5, 0.5, 0.0, //top point

        //triangle 2 Shift Right
        0.0, 0.5, 0.0, //left point
        1.0, 0.5, 0.0, //right point
        0.5, -0.5, 0.0, //top point
};

float InitOpenGL::verticesRect[12] = {
    //rectangle points   
    0.5, 0.5, 0.0, //top right
    0.5, -0.5, 0.0, //bottom right
    -0.5, -0.5, 0.0, //bottom left
    -0.5, 0.5, 0.0, //top left
};

unsigned int InitOpenGL::verticesRectIndices[6] = {
    0, 1, 3, //first traingle
    1, 2, 3, //second triangle
};


