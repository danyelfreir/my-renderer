#include "Shader.h"
#include <OpenGL/gl3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shader_init(Shader *self, char *filepath, int pathLen) {
    size_t vertPathLen = pathLen + sizeof("/shaders/vertex.glsl") + 1;
    char vertPath[vertPathLen];
    strcpy(vertPath, filepath);
    strcpy(vertPath + pathLen, "/shaders/vertex.glsl");
    FILE *vertexFile = fopen(vertPath, "r");
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertexFile) {
        fprintf(stderr, "Could not open vertex shader file\n");
        exit(1);
    }
    fseek(vertexFile, 0, SEEK_END);
    long length = ftell(vertexFile);
    rewind(vertexFile);
    char *vertexBuffer = (char *)malloc(length + 1);
    fread(vertexBuffer, 1, length, vertexFile);
    vertexBuffer[length] = '\0';
    fclose(vertexFile);
    glShaderSource(vertexShader, 1, &vertexBuffer, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "Vertex shader compilation failed: %s\n", infoLog);
        exit(1);
    }
    size_t fragPathLen = pathLen + sizeof("/shaders/fragment.glsl") + 1;
    char fragPath[fragPathLen];
    strcpy(fragPath, filepath);
    strcpy(fragPath + pathLen, "/shaders/fragment.glsl");
    printf("%s\n", fragPath);
    FILE *fragmentFile = fopen(fragPath, "r");
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragmentFile) {
        fprintf(stderr, "Could not open fragment shader file\n");
        exit(1);
    }
    fseek(fragmentFile, 0, SEEK_END);
    length = ftell(fragmentFile);
    rewind(fragmentFile);
    // char fragmentBuffer[length + 1];
    char *fragmentBuffer = (char *)malloc(length + 1);
    fread(fragmentBuffer, 1, length, fragmentFile);
    fragmentBuffer[length] = '\0';
    fclose(fragmentFile);
    glShaderSource(fragmentShader, 1, &fragmentBuffer, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "Fragment shader compilation failed: %s\n", infoLog);
        exit(1);
    }
    self->programId = glCreateProgram();
    glAttachShader(self->programId, vertexShader);
    glAttachShader(self->programId, fragmentShader);
    glLinkProgram(self->programId);

    glGetProgramiv(self->programId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(self->programId, 512, NULL, infoLog);
        fprintf(stderr, "Shader program linking failed: %s\n", infoLog);
        exit(1);
    }

    self->positions = glGetAttribLocation(self->programId, "a_position");
    self->normals = glGetAttribLocation(self->programId, "a_normal");
    self->modelMatrix = glGetUniformLocation(self->programId, "u_model_matrix");
    self->viewMatrix = glGetUniformLocation(self->programId, "u_view_matrix");
    self->projectionMatrix = glGetUniformLocation(self->programId, "u_projection_matrix");
    self->materialDiffuse = glGetUniformLocation(self->programId, "u_material.diffuse");
    self->materialSpecular = glGetUniformLocation(self->programId, "u_material.specular");
    self->materialAmbient = glGetUniformLocation(self->programId, "u_material.ambient");
    self->materialShininess = glGetUniformLocation(self->programId, "u_material.shininess");
    self->positionLightPosition = glGetUniformLocation(self->programId, "u_position_light.position");
    self->positionLightDiffuse = glGetUniformLocation(self->programId, "u_position_light.diffuse");
    self->positionLightSpecular = glGetUniformLocation(self->programId, "u_position_light.specular");
    self->positionLightAmbient = glGetUniformLocation(self->programId, "u_position_light.ambient");
    self->cameraPosition = glGetUniformLocation(self->programId, "u_camera_position");

    glEnableVertexAttribArray(self->positions);
    glEnableVertexAttribArray(self->normals);

    free(vertexBuffer);
    free(fragmentBuffer);
}

void shader_use(Shader *self) {
    glUseProgram(self->programId);
}

void shader_setModelMatrix(Shader *self, Matrix4 *modelMatrix) {
    glUniformMatrix4fv(self->modelMatrix, 1, GL_TRUE, modelMatrix->matrix);
}

void shader_setViewMatrix(Shader *self, Matrix4 *viewMatrix) {
    glUniformMatrix4fv(self->viewMatrix, 1, GL_TRUE, viewMatrix->matrix);
}

void shader_setProjectionMatrix(Shader *self, Matrix4 *projectionMatrix) {
    glUniformMatrix4fv(self->projectionMatrix, 1, GL_TRUE, projectionMatrix->matrix);
}

void shader_setPosition(Shader *self, float *positions) {
    // GLuint vertexBuffer, vertexArray;
    // glGenBuffers(1, &vertexBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), positions, GL_STATIC_DRAW);

    // glGenVertexArrays(1, &vertexArray);
    // glBindVertexArray(vertexArray);
    // glEnableVertexAttribArray(self->positions);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // glVertexAttribPointer(self->positions, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glVertexAttribPointer(self->positions, 3, GL_FLOAT, GL_FALSE, 0, positions);
}

void shader_setNormals(Shader *self, float *normals) {
    // GLuint vertexBuffer, vertexArray;
    // glGenBuffers(1, &vertexBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), normals, GL_STATIC_DRAW);

    // glGenVertexArrays(1, &vertexArray);
    // glBindVertexArray(vertexArray);
    // glEnableVertexAttribArray(self->normals);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    
    glVertexAttribPointer(self->normals, 3, GL_FLOAT, GL_FALSE, 0, normals);
}

void shader_setMaterial(Shader *self, Material *material) {
    glUniform4f(self->materialDiffuse, material->diffuse.x, material->diffuse.y, material->diffuse.z, 1.0);
    glUniform4f(self->materialSpecular, material->specular.x, material->specular.y, material->specular.z, 1.0);
    glUniform4f(self->materialAmbient, material->ambient.x, material->ambient.y, material->ambient.z, 1.0);
    glUniform1f(self->materialShininess, material->shininess);
}

void shader_setPositionLight(Shader *self, PositionLight *positionLight) {
    glUniform4f(self->positionLightPosition, positionLight->position.x, positionLight->position.y, positionLight->position.z, 1.0);
    glUniform4f(self->positionLightDiffuse, positionLight->diffuse.x, positionLight->diffuse.y, positionLight->diffuse.z, 1.0);
    glUniform4f(self->positionLightSpecular, positionLight->specular.x, positionLight->specular.y, positionLight->specular.z, 1.0);
    glUniform4f(self->positionLightAmbient, positionLight->ambient.x, positionLight->ambient.y, positionLight->ambient.z, 1.0);
}

void shader_setCameraPosition(Shader *self, Vector3 *cameraPosition) {
    glUniform4f(self->cameraPosition, cameraPosition->x, cameraPosition->y, cameraPosition->z, 1.0);
}
