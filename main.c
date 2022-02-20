#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printMatrix(double* matrix, double* rhs, int dimension){
    if (dimension > 5) {
        printf("Matrix is too large to print\n");
        return;
    }
    printf("MATRIX:\n\n");
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension-1; j++){
            printf("%.2lf\t|\t", matrix[i*dimension+j]);
        }
        printf("%.2lf\t|||\t%.2lf\n", matrix[(i+1)*dimension-1], rhs[i]);
    }
    printf("\n");
}

void solveMatrix(double* matrix, double* rhs, int dimension){
    printf("DIAGONALISIERUNG DER MATRIX:\n");
    for(int i = 0; i < dimension-1; i++){
        for(int j = 0; j < dimension-(i+1); j++){
            double factor = matrix[(j+i+1)*dimension+i]/matrix[i*dimension+i];
            for(int k = 0; k < dimension; k++){
                matrix[(j+i+1)*dimension+k] = matrix[(j+i+1)*dimension+k] - matrix[i*dimension+k]*factor;
            }
            rhs[j+i+1] = rhs[j+i+1] - rhs[i]*factor;
        }
    }
    printMatrix(matrix, rhs, dimension);
    for (int i = 0; i < dimension; i++)
    {
        double divisor = matrix[i*dimension+i];
        rhs[i] = rhs[i] / divisor;
        for (int j = 0; j < dimension; j++)
        {
            matrix[i*dimension+j] = matrix[i*dimension+j] / divisor;
        }
    }
    printf("1 AUF DER DIAGONALEN:\n");
    printMatrix(matrix, rhs, dimension);

    double *solutionVec = malloc(sizeof(double) * dimension);
    solutionVec[dimension-1] = rhs[dimension-1];

    for(int i = dimension-2; i >= 0; i--){
        double subtrahend = 0;
        for(int j = 0; j < dimension-i-1; j++){
            subtrahend += matrix[i*dimension+(dimension-(j+1))] * solutionVec[dimension-1-j];
        }
        solutionVec[i] = rhs[i] - subtrahend;
    }
    printf("SOLUTION VECTOR:\n");
    for(int i = 0; i < dimension; i++){
        printf("x%d\t= %lf\n", (i+1), solutionVec[i]);
    }
    printf("\n");
}

void GaussInit(){
    char *fileOptions[] = {
        "dim_large.txt",
        "dim_small.txt",
        "dim1.txt",
        "dim2.txt",
        "dim3.txt",
        "dim4.txt",
        "dim5.txt",
        "matrix_large.txt",
        "matrix_small.txt",
        "matrix1.txt",
        "matrix2.txt",
        "matrix3.txt",
        "matrix4.txt",
        "matrix5.txt",
        "rhs_large.txt",
        "rhs_small.txt",
        "rhs1.txt",
        "rhs2.txt",
        "rhs3.txt",
        "rhs4.txt",
        "rhs5.txt",
    };

    int pickOfFileset;
    printf("Which fileset do you want to work with?\n");
    scanf("%d", &pickOfFileset);

    FILE *dim = fopen(fileOptions[(pickOfFileset-1)], "r");
    FILE *matrx = fopen(fileOptions[(pickOfFileset-1)+7], "r");
    FILE *righths = fopen(fileOptions[(pickOfFileset-1)+14], "r");
    if (dim == NULL || matrx == NULL || righths == NULL)
    {
        printf("ERROR: Could not open file");
        return;
    }

    int dimension;
    fscanf(dim, "%d", &dimension);
    double *matrix = malloc(sizeof(double) * pow(dimension, 2));
    double *rhs = malloc(sizeof(double) * dimension);

    for(int i = 0; i < (pow(dimension, 2)); i++){
        fscanf(matrx, "%lf", &matrix[i]);
    }
    for (int i = 0; i < dimension; i++)
    {
        fscanf(righths, "%lf", &rhs[i]);
    }
    
    printMatrix(matrix, rhs, dimension);
    
    solveMatrix(matrix, rhs, dimension);
}

int main(){
    system("cls");

    GaussInit();

    return 0;
}