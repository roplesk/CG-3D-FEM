#include "common.hpp"
#include "shader.hpp"
#include "buffer.hpp"

const int WINDOW_WIDTH =  800;
const int WINDOW_HEIGHT = 800;

// called whenever the window gets resized
void
resizeCallback(GLFWwindow* window, int width, int height);

int
main(int, char* argv[]) {
    GLFWwindow* window = initOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, argv[0]);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    // load and compile shaders and link program
    unsigned int vertexShader = compileShader("basic_colors.vert", GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader("basic_colors.frag", GL_FRAGMENT_SHADER);
    unsigned int shaderProgram = linkProgram(vertexShader, fragmentShader);
    // after linking the program the shader objects are no longer needed
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    // vertex data
    float vertex_data[] = {
        -0.5f, -0.5f, 0.0f, 1.f, 0.f, 0.f, 1.f,
         0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f, 1.f,
         0.0f,  0.5f, 0.0f, 0.f, 0.f, 1.f, 1.f
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = makeBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertex_data), vertex_data);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    unsigned int IBO = makeBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(indices), indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // rendering loop
    while (glfwWindowShouldClose(window) == false) {
        // set background color...
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        // and fill screen with it (therefore clearing the window)
        glClear(GL_COLOR_BUFFER_BIT);

        // render something...
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) 0);

        // swap buffers == show rendered content
        glfwSwapBuffers(window);
        // process window events
        glfwPollEvents();
    }


    glfwTerminate();
}

void resizeCallback(GLFWwindow*, int width, int height)
{
    // set new width and height as viewport size
    glViewport(0, 0, width, height);
}
