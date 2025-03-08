#pragma once

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

void v3_add(Vector3 *self, Vector3 *other);
void v3_sub(Vector3 *self, Vector3 *other);
void v3_mul(Vector3 *self, float scalar);
float v3_len(Vector3 *self);
void v3_normalize(Vector3 *self);
float v3_dot(Vector3 *self, Vector3 *other);
void v3_cross(Vector3 *self, Vector3 *other, Vector3 *result);
void v3_print(Vector3 *self);

