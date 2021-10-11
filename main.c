#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define DELIM ","

double determinant(
  double const * const * const matrix,
  int const dim
);

void setup(
  FILE * * const file_p,
  char const * const path,
  int * const dim_p,
  double * * * const matrix
);

void clean_up(
  FILE * file,
  int const dim,
  double * * matrix
);

void check_square_err(
  int const dim,
  double * * matrix
);

void parse_matrix(
  FILE * file,
  double * * * const matrix_p
);

int main(
  int const argc,
  char const * const * const argv
) {

  // example usage
  if (argc != 2) {
    fprintf(stderr, "Example usage: %s matrix.txt\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE * file;
  double * * matrix;
  int dim;
  setup(&file, argv[1], &dim, &matrix);

  // calculating the determinant
  double const det = determinant(
    (double const * const * const) matrix,
    dim
  );
  printf("%f\n", det);


  clean_up(file, dim, matrix);

  return EXIT_SUCCESS;
}

void setup(
  FILE * * const file_p,
  char const * const path,
  int * const dim_p,
  double * * * const matrix_p
) {
  // opening the file
  *file_p = fopen(path, "r");
  if (*file_p == NULL) {
    perror(NULL);
    fprintf(stderr, "Could not find %s\n", path);
    exit(EXIT_FAILURE);
  }


  // parsing the matrix
  parse_matrix(*file_p, matrix_p);

  // checking if it is square
  int const dim = arrlen(*matrix_p);
  *dim_p = dim;
  check_square_err(dim, *matrix_p);
}

void clean_up(
  FILE * file,
  int const dim,
  double * * matrix
) {
  for (int i = 0; i < dim; ++i) {
    arrfree(matrix[i]);
  }
  arrfree(matrix);
  fclose(file);
}

void check_square_err(
  int const dim,
  double * * matrix
) {
  for (int i = 0; i < dim; ++i) {
    if (arrlen(matrix[i]) != dim) {
      fprintf(stderr,
        "Try with a square matrix (comma separated)\n"
        "For example:\n"
        "1.01  ,  -0.02,   0\n"
        " 4    ,  -5   , 5.05\n"
        " 0    ,  -3   , 1\n"
      );
      exit(EXIT_FAILURE);
    }
  }
}

void parse_matrix(
  FILE * file,
  double * * * const matrix_p
) {
  char line[20];
  *matrix_p = NULL;
  while (fgets(line, 20, file)) {
    char *token = strtok(line, DELIM);
    double *row = NULL;
    while (token != NULL) {
      double number = atof(token);
      arrput(row, number);
      token = strtok(NULL, DELIM);
    }
    arrput(*matrix_p, row);
    printf("\n");
  }
}
