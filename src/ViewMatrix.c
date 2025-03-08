#include "ViewMatrix.h"

void vm_lookAt(ViewMatrix *self, Vector3 *eye, Vector3 *center, Vector3 *up) {
    self->eye.x = eye->x;
    self->eye.y = eye->y;
    self->eye.z = eye->z;

    v3_sub(eye, center);
    self->n.x = eye->x;
    self->n.y = eye->y;
    self->n.z = eye->z;
    v3_normalize(&self->n);

    v3_cross(up, &self->n, &self->u);
    v3_normalize(&self->u);

    v3_cross(&self->n, &self->u, &self->v);
    v3_normalize(&self->v);
}

void vm_getMatrix(ViewMatrix *self, Matrix4 *result) {
    Vector3 minusEye = { -self->eye.x, -self->eye.y, -self->eye.z };
    Matrix4 matrix = {
        self->u.x, self->u.y, self->u.z, v3_dot(&minusEye, &self->u),
        self->v.x, self->v.y, self->v.z, v3_dot(&minusEye, &self->v),
        self->n.x, self->n.y, self->n.z, v3_dot(&minusEye, &self->n),
        0, 0, 0, 1
    };
    for (int i = 0; i < 16; i++) {
        result->matrix[i] = matrix.matrix[i];
    }
}