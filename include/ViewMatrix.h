#pragma once
#include "Vector3.h"
#include "Matrix4.h"

typedef struct {
    Vector3 eye;
    Vector3 u;
    Vector3 v;
    Vector3 n;
} ViewMatrix;

void vm_lookAt(ViewMatrix *self, Vector3 *eye, Vector3 *center, Vector3 *up);
void vm_getMatrix(ViewMatrix *self, Matrix4 *result);
