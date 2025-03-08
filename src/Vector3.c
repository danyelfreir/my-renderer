#include "Vector3.h"
#include <math.h>
#include <stdio.h>

void v3_add(Vector3 *self, Vector3 *other) {
    self->x += other->x;
    self->y += other->y;
    self->z += other->z;
}

void v3_sub(Vector3 *self, Vector3 *other) {
    self->x -= other->x;
    self->y -= other->y;
    self->z -= other->z;
}

void v3_mul(Vector3 *self, float scalar) {
    self->x *= scalar;
    self->y *= scalar;
    self->z *= scalar;
}

float v3_len(Vector3 *self) {
    return sqrt(self->x * self->x + self->y * self->y + self->z * self->z);
}

void v3_normalize(Vector3 *self) {
    float len = v3_len(self);
    self->x /= len;
    self->y /= len;
    self->z /= len;
}

float v3_dot(Vector3 *self, Vector3 *other) {
    return self->x * other->x + self->y * other->y + self->z * other->z;
}

void v3_cross(Vector3 *self, Vector3 *other, Vector3 *result) {
    result->x = self->y * other->z - self->z * other->y;
    result->y = self->z * other->x - self->x * other->z;
    result->z = self->x * other->y - self->y * other->x;
}

void v3_print(Vector3 *self) {
    printf("Vector3(%d, %d, %d)\n", self->x, self->y, self->z);
}