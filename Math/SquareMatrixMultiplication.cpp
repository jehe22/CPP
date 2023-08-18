#include <iostream>

// this function takes the reference of ordo AND the reference of first element of array
void setValueOfMatrices(short *ordo, float *the_matrix) {
    // counter and bufffer are used for tracking index since this use pointer/reference
    short counter = 0;
    for (short i = 0; i < *ordo; i++) {
        short buffer = 0;
        for (short j = 0; j < *ordo; j++) {
            std::cout << "Value of [" << i << "][" << j << "]: ";
            std::cin >> (the_matrix + counter)[j];
            buffer = j + 1;
        }
        counter = counter + buffer;
    }
}

// this function print a square matrix to console
void printToConsole(short *ordo, float *the_matrix) {
    short counter = 0;
    for (short i = 0; i < *ordo; i++) {
        short buffer = 0;
        for (short j = 0; j < *ordo; j++) {
            std::cout << (the_matrix + counter)[j] << "\t";
            buffer = j + 1;
        }
        counter = counter + buffer;
        std::cout << "\n\n";
    }
}

int main() {
    // user can input the ordo
    short ordo = 0;
    std::cout << "Ordo matriks: ";
    std::cin >> ordo;

    // set the dimension
    float matrix_a[ordo][ordo];
    float matrix_b[ordo][ordo];
    float matrix_c[ordo][ordo];

    // go to the function to handle setting array value from user input
    std::cout << "Set the A Matrix\n";
    setValueOfMatrices(&ordo, &(matrix_a[0][0]));
    std::cout << "Set the B Matrix\n";
    setValueOfMatrices(&ordo, &(matrix_b[0][0]));

    // the actual multiplication
    for (short i = 0; i < ordo; i++) {
        for (short j = 0; j < ordo; j++) {
            float buffer = 0;
            for (short k = 0; k < ordo; k++) {
                buffer = buffer + (matrix_a[i][k] * matrix_b[k][j]);
            }
            matrix_c[i][j] = buffer;
        }
    }

    // for print-to-console only
    std::cout << "A:\n";
    printToConsole(&ordo, &matrix_a[0][0]);
    std::cout << "B:\n";
    printToConsole(&ordo, &matrix_b[0][0]);
    std::cout << "C = AB:\n";
    printToConsole(&ordo, &matrix_c[0][0]);

    // halt -- just pass 0
    std::cin >> ordo;

    return 0;
}
