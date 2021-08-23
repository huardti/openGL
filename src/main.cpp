// http://docs.gl/

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/error.hpp"
#include "renderer/shader_compiler.hpp"

#include "renderer/indexBuffer.hpp"
#include "renderer/vertexBuffer.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!status) {
        std::cout << "error when loading Glad !!" << std::endl;
        return -1;
    }

    /* print openGL version */
    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
    /* Loop until the user closes the window */
    float positions[] {
        -0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f,  0.5f,
    };

    unsigned int indices[] {
        0, 1, 2,
        0, 1, 3
    };

    unsigned int vao;
    glCall(glGenVertexArrays(1, &vao));
    glCall(glBindVertexArray(vao));

    vertexBuffer vb(positions, 4 * 2 * sizeof(float));

    glCall(glEnableVertexAttribArray(0));
    glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    indexBuffer ib(indices, 6);

    shader programShader("resources/shader/basic/vertex.shader", "resources/shader/basic/fragment.shader");
    glCall(glUseProgram(programShader.getProgramID()));

    int uniform_color = glGetUniformLocation(programShader.getProgramID(), "u_Color");
    // programShader.printFragmentShader();
    float r = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glCall(glClear(GL_COLOR_BUFFER_BIT));
        glCall(glUniform4f(uniform_color, r, 0.3f, 0.5f, 1.0f));

        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        r += 0.01f;
        if (r > 1.0f) {
            r=0.0f;
        }

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}