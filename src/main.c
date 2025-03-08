#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#include "ModelMatrix.h"
#include "ProjectionMatrix.h"
#include "Shader.h"
#include "Shapes.h"
#include "Block.h"
#include "ViewMatrix.h"
#include "Vector3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int COLS = 5;
const int ROWS = 9;

static GLfloat currentAngleOfRotation = 0.0;
static ModelMatrix modelMatrix;
static ViewMatrix viewMatrix;
static ProjectionMatrix projectionMatrix;
static Shader shader;
static Material blockMaterial;
Block blocks[COLS * ROWS];
static Cube cube;
static Sphere sphere;
// static Spaceship spaceship;
static Material blockMaterial;
static Material sphereMaterial;
static PositionLight positionLight;

void init(char *resourcesPath, int pathLength) {
    const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte *version = glGetString(GL_VERSION);   // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glViewport(0, 0, 500, 500);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    Vector3 eye = {0.0, 1.0, 9.0};
    Vector3 center = {0.0, 0.0, 0.0};
    Vector3 up = {0.0, 1.0, 0.0};
    vm_lookAt(&viewMatrix, &eye, &center, &up);
    shader_init(&shader, resourcesPath, pathLength);
    shader_use(&shader);
    cube_init(&cube);
    for (int z = 0; z < ROWS; z++) {
        for (int x = 0; x < COLS; x++) {
            blocks[z * ROWS + x].cube = &cube;
            blocks[z * ROWS + x].position.x = x - 2;
            blocks[z * ROWS + x].position.y = 0;
            blocks[z * ROWS + x].position.z = z;
        }
    }
    sphere_init(&sphere);
    // spaceship_init(&spaceship);
    Matrix4 mMatrix;
    Matrix4 vMatrix;
    mm_identity(&modelMatrix);
    mm_getMatrix(&modelMatrix, &mMatrix);
    vm_getMatrix(&viewMatrix, &vMatrix);
    shader_setViewMatrix(&shader, &vMatrix);
    blockMaterial = (Material){
        .diffuse = {1, 0, 0},
        .specular = {1, 1, 1},
        .ambient = {0.5, 0.0, 0.0},
        .shininess = 20.0
    };
    sphereMaterial = (Material) {
        .diffuse = {0, 0, 1},
        .specular = {1, 1, 1},
        .ambient = {0.5, 0.0, 0.0},
        .shininess = 20.0
    };
    positionLight = (PositionLight){
        .position = {9.0, 9.0, 0.0},
        .diffuse = {0.3, 0, 0},
        .specular = {0.7, 0.7, 0.7},
        .ambient = {0.0, 0.0, 0.0},
    };
    shader_setPositionLight(&shader, &positionLight);
    shader_setCameraPosition(&shader, &eye);
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    pm_perspective(&projectionMatrix, 45.0, aspect, 0.1, 100.0);
    Matrix4 pMatrix;
    pm_getMatrix(&projectionMatrix, &pMatrix);
    shader_setProjectionMatrix(&shader, &pMatrix);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4 mMatrix;

    cube_setVertices(&cube, &shader);
    shader_setPositionLight(&shader, &positionLight);

    shader_setMaterial(&shader, &blockMaterial);
    for (int i = 0; i < ROWS * COLS; i++) {
        Block b = blocks[i];
        mm_push(&modelMatrix);
        mm_translate(&modelMatrix, b.position.x, b.position.y, b.position.z);
        mm_scale(&modelMatrix, 0.8, 0.8, 0.8);
        mm_getMatrix(&modelMatrix, &mMatrix);
        shader_setModelMatrix(&shader, &mMatrix);
        cube_draw(b.cube);
        mm_pop(&modelMatrix);
    }

    shader_setMaterial(&shader, &sphereMaterial);
    sphere_setVertices(&sphere, &shader);
    mm_push(&modelMatrix);
    mm_translate(&modelMatrix, 0.0, 1.0, 0.0);
    shader_setModelMatrix(&shader, &modelMatrix.matrix);
    sphere_draw(&sphere);
    mm_pop(&modelMatrix);

    glutSwapBuffers();
}

void timer(int v) {
    currentAngleOfRotation += 1.0;
    if (currentAngleOfRotation > 360.0) {
        currentAngleOfRotation -= 360.0;
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}

void mouse(int button, int state, int x, int y) {}

void keyboard(unsigned char key, int x, int y) { printf("key: %d - x: %d - y: %d\n", key, x, y); }

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Missing resources file path\n");
        exit(-1);
    }
    char *resourcesFilepath = argv[1];
    size_t resourcesFilepathLen = strlen(resourcesFilepath);
    if (resourcesFilepathLen < 0) {
        perror("strlen\n");
    }
    printf("%s\n", resourcesFilepath);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Spinning Square");
    init(resourcesFilepath, resourcesFilepathLen);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
