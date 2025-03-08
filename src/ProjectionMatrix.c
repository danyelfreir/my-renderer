#include <math.h>
#include "ProjectionMatrix.h"

void pm_perspective(ProjectionMatrix *self, float fov, float aspect, float near, float far) {
    self->left = -near * tan(fov / 2);
    self->right = near * tan(fov / 2);
    self->bottom = -near * tan(fov / 2) / aspect;
    self->top = near * tan(fov / 2) / aspect;
    self->near = near;
    self->far = far;
}

void pm_ortho(ProjectionMatrix *self, float left, float right, float bottom, float top, float near, float far) {
    self->left = left;
    self->right = right;
    self->bottom = bottom;
    self->top = top;
    self->near = near;
    self->far = far;
}

void pm_getMatrix(ProjectionMatrix *self, Matrix4 *result) {
    if (self->isOrthographic) {
        float A = 2 / (self->right - self->left);
        float B = -(self->right + self->left) / (self->right - self->left);
        float C = 2 / (self->top - self->bottom);
        float D = -(self->top + self->bottom) / (self->top - self->bottom);
        float E = 2 / (self->near - self->far);
        float F = (self->near + self->far) / (self->near - self->far);
        Matrix4 m = {
            .matrix = {
                A, 0, 0, B,
                0, C, 0, D,
                0, 0, E, F,
                0, 0, 0, 1
            }
        };
        for (int i = 0; i < 16; i++) {
            result->matrix[i] = m.matrix[i];
        }
    } else {
        float A = (2 * self->near) / (self->right - self->left);
        float B = (self->right + self->left) / (self->right - self->left);
        float C = (2 * self->near) / (self->top - self->bottom);
        float D = (self->top + self->bottom) / (self->top - self->bottom);
        float E = -(self->far + self->near) / (self->far - self->near);
        float F = -2 * self->far * self->near / (self->far - self->near);
        Matrix4 m = {
            .matrix = {
                A, 0, B, 0,
                0, C, D, 0,
                0, 0, E, F,
                0, 0, -1, 0
            }
        };
        for (int i = 0; i < 16; i++) {
            result->matrix[i] = m.matrix[i];
        }
    }
}