#include <stdio.h>
#include "Matrix4.h"

void m4_add(Matrix4 *self, Matrix4 *other) {
    int counter = 0;
    float new_matrix[16] = {0};
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            for (int i = 0; i < 4; i++) {
                new_matrix[counter] += self->matrix[row * 4 + i] * other->matrix[col + 4 * i];
            }
            counter++;
        }
    }
    for (int i = 0; i < 16; i++) {
        self->matrix[i] = new_matrix[i];
    }
}

void m4_print(Matrix4 *self) {
    printf("[\n");
    for (int i = 0; i < 16; i++) {
        printf("%f ", self->matrix[i]);
        if (i % 4 == 3) {
            printf("\n\t");
        }
    }
    printf("]\n");
}