#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRINT_DIM 20

void initHilbert(float * data, int rows, int columns);
void printMat(float * data, int rows, int columns);
void initConst(float * data, int rows, int columns, float initVal);
void matVecProduct(float * matrix, float * vector, float * output, int rows,
                   int columns);
float matSum(float * matrix, int rows, int columns);
void doBasicDemoMultiplication(int rows, int columns);
void doBenchmark(int rows, int columns);


/**
 * start the program
 */
int main(int argc, char * argv[]){
  if(argc < 3){
    fprintf(stderr, "Not enough arguments!\nUsage: %s rows columns\n", argv[0]);
    return -1;
  }
  int benchmarkMode = 0;
  if(strcmp("-b", argv[1]) == 0){
    benchmarkMode = 1;
    if(argc < 4){
      fprintf(stderr, "Not enough arguments!\nUsage: %s -b rows columns\n",
              argv[0]);
      return -1;
    }
  }
  long rows    = strtol(argv[1 + benchmarkMode], NULL, 10);
  long columns = strtol(argv[2 + benchmarkMode], NULL, 10);

  if(benchmarkMode){
    doBenchmark(rows, columns);
  } else {
    doBasicDemoMultiplication(rows, columns);
  }
}

void doBenchmark(int rows, int columns){}

/**
 * does a multiplication and prints the result
 *
 * @param rows the number of rows to use
 * @param columns the number of columns to use
 */
void doBasicDemoMultiplication(int rows, int columns){
  float matrix[rows * columns];
  initHilbert(&matrix[0], rows, columns);

  float vector[columns];
  initConst(&vector[0], rows, 1, 1);

  float output[rows];
  matVecProduct(&matrix[0], &vector[0], &output[0], rows, columns);

  int shouldPrint = rows <= MAX_PRINT_DIM && columns <= MAX_PRINT_DIM;

  if(shouldPrint){
    printf("Matrix:\n");
    printMat(&matrix[0], rows, columns);
    printf("Vector\n");
    printMat(&vector[0], columns, 1);
    printf("Product\n");
    printMat(&output[0], 1, rows);
  } else {
    printf("Too many elements to print nicely\n");
  }

  printf("Sum\n");
  printf("%.4f\n", matSum(&output[0], rows, 1));
  printf("Expected sum\n");
  printf("%.4f\n", matSum(&matrix[0], rows, columns));
}

/**
 * Creats a hilbert matrix at the given data. The data is assumed to be in
 * row-major.
 *
 * @param data the data to fill (rows x columns matrix in row-major)
 * @param rows the number of rows
 * @param columns the number of columns
 */
void initHilbert(float * data, int rows, int columns){
  for(int c = 0; c < columns; c++){
    for(int r = 0; r < rows; r++){
      int index = c * rows + r;
      // value is c + r + 1 not c + r - 1 b/c c & r start at 0
      data[index] = 1.0 / ( c + r + 1 );
    }
  }
}

/**
 * prints a matrix to stdout
 *
 * @param data the matrix to print in row-major
 * @param rows the number of rows
 * @param columns the number of columns
 */
void printMat(float * data, int rows, int columns){
  for(int r = 0; r < rows; r++){
    for(int c = 0; c < columns; c++){
      int index = c * rows + r;
      printf("%.3f ", data[index]);
    }
    printf("\n");
  }
}

/**
 * Initialises a matrix with a constant value.
 *
 * @param data the matrix in row-major order
 * @param rows the number of rows
 * @param columns the number of columns
 * @param initVal the value to initialise the matrix with
 */
void initConst(float * data, int rows, int columns, float initVal){
  for(int c = 0; c < columns; c++){
    for(int r = 0; r < rows; r++){
      int index = c * rows + r;
      data[index] = initVal;
    }
  }
}

/**
 * compute the matrix vector product between the given matrix and vector.
 *
 * @param matrix the matrix to be used for multiplication. (row-major)
 * @param vector the vector to be used in multiplication.
 * @param output the output vector (must be at least rows long)
 * @param rows the number of rows in the matrix
 * @param columns the number of columns in the matrix
 */
void matVecProduct(float * matrix, float * vector, float * output, int rows,
                   int columns){
  for(int r = 0; r < rows; r++){
    output[r] = 0;
    for(int c = 0; c < columns; c++){
      int index = c * rows + r;
      output[r] += vector[r] * matrix[index];
    }
  }
}

/**
 * Computes the element wise sum of the matrix.
 *
 * @param matrix the matrix to sum
 * @param the number of rows
 * @param the number of columns
 */
float matSum(float * matrix, int rows, int columns){
  float output = 0;
  for(int r = 0; r < rows; r++){
    for(int c = 0; c < columns; c++){
      int index = c * rows + r;
      output += matrix[index];
    }
  }
}
