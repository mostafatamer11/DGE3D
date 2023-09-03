#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>

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

    glEnableVertexAttribArray(0);

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
    }
	time_t end = time(NULL);
	std::cout << "\nfps avarage = " << (int)(f / (end - begin)) << "\nframes = " << f <<"\nseconds = " << (end - begin);
    glfwTerminate();
    return 0;
}