#pragma once
#include "Vector3.h"

typedef struct material {
    Vector3 diffuse;
    Vector3 specular;
    Vector3 ambient;
    float shininess;
} Material;

typedef struct positionLight {
    Vector3 position;
    Vector3 diffuse;
    Vector3 specular;
    Vector3 ambient;
} PositionLight;