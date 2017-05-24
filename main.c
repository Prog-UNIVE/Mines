#include "mines.h"
#include "matrix.h"


/*
int load_scheamtic(char *f_name, Mine * game) {
	int x, y, counter;

	FILE *file;
	file = fopen(f_name, "r");

	if (file) {
		counter = 0;

		while (!feof(file))
		{
			if (fscanf(file, "%d,%d", &x, &y))
			{
				printf("Line %d, x: %d, y: %d", counter, x, y);
			}

			counter++;
		}

		fclose(file);

		return 0;
	}

	return -1;
}*/

int print_matrix(Matrix matrix) {
	int i, j, x, y, *pi;

	x = Matrix_get_width(matrix);
	y = Matrix_get_height(matrix);

	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			if (Matrix_get(matrix, i, j, (void **)&pi) >= 0) {
				if (pi != NULL) {
					printf("%d ", *pi);
				}
				else {
					printf("NULL ");
				}
			}
		}
		printf("\n");
	}

	return 0;
}

int main(int argc, char *argv[]) {
	int x, y, z, i, j;
	int *pi;
	Matrix matrix;

	printf("Running....\n");

	x = 5;
	y = 7;
	z = 0;	

	if ((matrix = Matrix_init(x, y)) != NULL) {
		printf("Created the matrix....\n");

		print_matrix(matrix);

		z = 0;
		for (i = 0; i < x; i++) {
			for (j = 0; j < y; j++) {

				printf("Insert at %d, %d -> %d\n", i, j, z);

				if ((pi = (int *)malloc(sizeof(int))) == NULL) {
					printf("Error on heap\n");
					return 1;
				}

				*pi = z;
				Matrix_set(matrix, i, j, pi);
				z++;
			}
		}

		print_matrix(matrix);

		Matrix_destroy(matrix);
	}

	printf("press any key to terminate\n");
	getchar();
	return 0;
}