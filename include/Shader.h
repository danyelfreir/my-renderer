#pragma once

#include <OpenGL/gl.h>
#include "Matrix4.h"
#include "Vector3.h"
#include "ShaderObjects.h"

typedef struct {
    GLuint programId;
    GLint modelMatrix;
    GLint viewMatrix;
    GLint projectionMatrix;
    GLint positions;
    GLint normals;
    GLint materialSpecular;
    GLint materialDiffuse;
    GLint materialAmbient;
    GLint materialShininess;
    GLint positionLightPosition;
    GLint positionLightDiffuse;
    GLint positionLightSpecular;
    GLint positionLightAmbient;
    GLint cameraPosition;
} Shader;

void shader_init(Shader *self, char *filepath, int pathLen);
void shader_use(Shader *self);
void shader_setModelMatrix(Shader *self, Matrix4 *modelMatrix);
void shader_setViewMatrix(Shader *self, Matrix4 *viewMatrix);
void shader_setProjectionMatrix(Shader *self, Matrix4 *projectionMatrix);
void shader_setPosition(Shader *self, float *positions);
void shader_setNormals(Shader *self, float *normals);
void shader_setMaterial(Shader *self, Material *material);
void shader_setPositionLight(Shader *self, PositionLight *positionLight);
void shader_setCameraPosition(Shader *self, Vector3 *cameraPosition);