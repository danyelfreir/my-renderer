#include <math.h>
#include "Shapes.h"
#include <stdio.h>

void cube_init(Cube *self) {
    float points[] = {
        -0.5, -0.5, -0.5,
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, -0.5, 0.5,
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5, 0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        -0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5
    };
    float normals[] = {
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0
    };
    for (int i = 0; i < 72; i++) {
        self->positions[i] = points[i];
        self->normals[i] = normals[i];
    }
}

void cube_setVertices(Cube *self, Shader *shader) {
    shader_setPosition(shader, self->positions);
    shader_setNormals(shader, self->normals);
}

void cube_draw(Cube *self) {
    glDrawArrays(GL_QUADS, 0, 24);
}

void sphere_init(Sphere *self) {
    self->stacks = 12;
    self->slices = 24;
    self->vertexCount = 0;
    int index = 0;
    float stackInterval = M_PI / ((float)self->stacks);
    float sliceInterval = (2 * M_PI) / ((float)self->slices);

    for (int stack = 0; stack < self->stacks; stack++) {
        float stackAngle = (float)stack * stackInterval;
        for (int slice = 0; slice <= self->slices; slice++) {
            float sliceAngle = (float)slice * sliceInterval;
            self->positions[index++] = sinf(stackAngle) * cosf(sliceAngle);
            self->positions[index++] = cosf(stackAngle);
            self->positions[index++] = sinf(stackAngle) * sinf(sliceAngle);
            self->positions[index++] = sinf(stackAngle + stackInterval) * cosf(sliceAngle);
            self->positions[index++] = cosf(stackAngle + stackInterval);
            self->positions[index++] = sinf(stackAngle + stackInterval) * sinf(sliceAngle);
            self->vertexCount += 2;
        }
    }
}

void sphere_setVertices(Sphere *self, Shader *shader) {
    shader_setPosition(shader, self->positions);
    shader_setNormals(shader, self->positions);
}

void sphere_draw(Sphere *self) {
    for (int i = 0; i < self->vertexCount; i += ((self->slices + 1) * 2)) {
        glDrawArrays(GL_TRIANGLE_STRIP, i, (self->slices + 1) * 2);
    }
}

void spaceship_init(Spaceship *self) {
    float positions[] = {
            // ABC
            0.0, 0.25, 0.5,
            0.0, -0.25, 0.5,
            -1.0, 0.0, 1.0,
            // ABD
            0.0, 0.25, 0.5,
            0.0, -0.25, 0.5,
            1.0, 0.0, 1.0,
            // BDE
            0.0, -0.25, 0.5,
            1.0, 0.0, 1.0,
            0.0, 0.0, -1.0,
            // BCE
            0.0, -0.25, 0.5,
            -1.0, 0.0, 1.0,
            0.0, 0.0, -1.0,
            // ADE
            0.0, 0.25, 0.5,
            1.0, 0.0, 1.0,
            0.0, 0.0, -1.0,
            // ACE
            0.0, 0.25, 0.5,
            -1.0, 0.0, 1.0,
            0.0, 0.0, -1.0
    };
    float normals[] = {
            -0.25, 0.0, -0.5,
            -0.25, 0.0, -0.5,
            -0.25, 0.0, -0.5,

            -0.25, 0.0, 0.5,
            -0.25, 0.0, 0.5,
            -0.25, 0.0, 0.5,

            -0.5, 1.5, 0.25,
            -0.5, 1.5, 0.25,
            -0.5, 1.5, 0.25,

            -0.5, -1.5, -0.25,
            -0.5, -1.5, -0.25,
            -0.5, -1.5, -0.25,

            0.5, 1.5, -0.25,
            0.5, 1.5, -0.25,
            0.5, 1.5, -0.25,

            0.5, -1.5, 0.25,
            0.5, -1.5, 0.25,
            0.5, -1.5, 0.25,
    };
    for (int i = 0; i < 54; i++) {
        self->positions[i] = positions[i];
        self->normals[i] = normals[i];
    }
}

void spaceship_setVertices(Spaceship *self, Shader *shader) {
    shader_setPosition(shader, self->positions);
    shader_setNormals(shader, self->normals);
}

void spaceship_draw(Spaceship *self) {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 54 / 3);
}
