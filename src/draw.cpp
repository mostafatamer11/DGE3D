#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>

#include "include/draw.h"


static void clear()
{
    while (glGetError());
}


static void debug()
{
    while (GLenum error = glGetError())
    {
        fprintf(stderr, "[GL Error]:\n%d\n", error);
    }
    fflush(stderr);
}


void drawTriangle(triangle target, unsigned int bound_buffer, unsigned short indx)
{
    glEnableVertexAttribArray(indx);

    float vertices[9] = {
        target.p[0].x, target.p[0].y, target.p[0].z,
        target.p[1].x, target.p[1].y, target.p[1].z,
        target.p[2].x, target.p[2].y, target.p[2].z
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(indx, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 3, (const void*)0);

    clear();
    glDrawArrays(GL_TRIANGLES, 0, 9);
    debug();
}


int main(int argc, const char* argv[])
{
	time_t begin = time(NULL);
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "DGE3D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    fprintf(stdout, "GLEW version: %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "GL version: %s\n", glGetString(GL_VERSION));

    unsigned long long f = 0;

    unsigned int buffer;
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    triangle test = {200, 500, 100,  300, 500, 100,  250, 700, 100};

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    drawTriangle(test, buffer, 0);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
		glfwSwapInterval(1);
        f++;
        debug();
    }
	time_t end = time(NULL);
	std::cout << "\nfps avarage = " << (int)(f / (end - begin)) << "\nframes = " << f <<"\nseconds = " << (end - begin);
    glfwTerminate();
    return 0;
}