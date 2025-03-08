#pragma once
#include "Matrix4.h"

typedef struct {
    Matrix4 matrix;
    Matrix4 stack[4];
    int stackPointer;
} ModelMatrix;

void mm_identity(ModelMatrix *self);
void mm_push(ModelMatrix *self);
void mm_pop(ModelMatrix *self);
void mm_transform(ModelMatrix *self, Matrix4 *other);
void mm_translate(ModelMatrix *self, float x, float y, float z);
void mm_scale(ModelMatrix *self, float x, float y, float z);
void mm_rotateX(ModelMatrix *self, float angle);
void mm_rotateY(ModelMatrix *self, float angle);
void mm_rotateZ(ModelMatrix *self, float angle);
void mm_getMatrix(ModelMatrix *self, Matrix4 *result);
