#include <stdio.h>
#include <stdlib.h>

void initHilbert(float * data, int rows, int columns);

/**
 * start the program
 */
int main(int argc, char * argv[]){
  if(argc < 3){
    fprintf(stderr, "Not enough arguments!\nUsage: %s rows columns\n", argv[0]);
    return -1;
  }
  long rows = strtol(argv[1], NULL, 10);
  long columns = strtol(argv[2], NULL, 10);

  float data[rows * columns];
  initHilbert(&data[0], rows, columns);
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
      data[index] = 1.0 / (c + r + 1);
    }
  }
}
