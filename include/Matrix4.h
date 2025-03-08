#pragma once

typedef struct {
    float matrix[16];
} Matrix4;

void m4_add(Matrix4 *self, Matrix4 *other);
void m4_cross(Matrix4 *self, Matrix4 *other, Matrix4 *result);
void m4_print(Matrix4 *self);