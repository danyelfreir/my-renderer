#pragma once
#include "Matrix4.h"

typedef struct {
    float left, right, bottom, top, near, far;
    bool isOrthographic;
} ProjectionMatrix;

void pm_perspective(ProjectionMatrix *self, float fov, float aspect, float near, float far);
void pm_ortho(ProjectionMatrix *self, float left, float right, float bottom, float top, float near, float far);
void pm_getMatrix(ProjectionMatrix *self, Matrix4 *result);