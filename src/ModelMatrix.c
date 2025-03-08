#include "ModelMatrix.h"
#include <math.h>

void mm_identity(ModelMatrix *self) {
    self->matrix = (Matrix4) {{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }};
}

void mm_push(ModelMatrix *self) {
    if (self->stackPointer < 4) {
        self->stack[self->stackPointer++] = self->matrix;
    }
}

void mm_pop(ModelMatrix *self) {
    if (self->stackPointer > 0) {
        self->matrix = self->stack[--self->stackPointer];
    }
}

void mm_transform(ModelMatrix *self, Matrix4 *other) {
    m4_add(&self->matrix, other);
}

void mm_translate(ModelMatrix *self, float x, float y, float z) {
    Matrix4 translation = {{
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    }};
    mm_transform(self, &translation);
}

void mm_scale(ModelMatrix *self, float x, float y, float z) {
    Matrix4 scale = {{
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    }};
    mm_transform(self, &scale);
}

void mm_rotateX(ModelMatrix *self, float angle) {
    float rad = angle * M_PI / 180;
    float cos = cosf(rad);
    float sin = sinf(rad);
    Matrix4 rotation = {{
        1, 0, 0, 0,
        0, cos, -sin, 0,
        0, sin, cos, 0,
        0, 0, 0, 1
    }};
    mm_transform(self, &rotation);
}

void mm_rotateY(ModelMatrix *self, float angle) {
    float rad = angle * M_PI / 180;
    float cos = cosf(rad);
    float sin = sinf(rad);
    Matrix4 rotation = {{
        cos, 0, sin, 0,
        0, 1, 0, 0,
        -sin, 0, cos, 0,
        0, 0, 0, 1
    }};
    mm_transform(self, &rotation);
}

void mm_rotateZ(ModelMatrix *self, float angle) {
    float rad = angle * M_PI / 180;
    float cos = cosf(rad);
    float sin = sinf(rad);
    Matrix4 rotation = {{
        cos, -sin, 0, 0,
        sin, cos, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }};
    mm_transform(self, &rotation);
}

void mm_getMatrix(ModelMatrix *self, Matrix4 *result) {
    for (int i = 0; i < 16; i++) {
        result->matrix[i] = self->matrix.matrix[i];
    }
}
