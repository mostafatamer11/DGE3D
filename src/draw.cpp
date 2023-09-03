#include <GL/glew.h>

#include "draw.h"



void drawTriangle(triangle target, unsigned int bound_buffer, unsigned short indx)
{
    glEnableVertexAttribArray(indx);

    float vertices[9] = {
        target.p[0].x, target.p[0].y, target.p[0].z,
        target.p[1].x, target.p[1].y, target.p[1].z,
        target.p[2].x, target.p[2].y, target.p[2].z
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(indx, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);
}