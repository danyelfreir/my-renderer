#pragma once
#include "Shader.h"

typedef struct {
    float positions[72];
    float normals[72];
} Cube;

void cube_init(Cube *self);
void cube_setVertices(Cube *self, Shader *shader);
void cube_draw(Cube *self);

typedef struct {
    float positions[1800];
    int stacks, slices, vertexCount;
} Sphere;

void sphere_init(Sphere *self);
void sphere_setVertices(Sphere *self, Shader *shader);
void sphere_draw(Sphere *self);

typedef struct {
    float positions[54];
    float normals[54];
} Spaceship;

void spaceship_init(Spaceship *self);
void spaceship_setVertices(Spaceship *self, Shader *shader);
void spaceship_draw(Spaceship *self);
