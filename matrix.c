#include "matrix.h"

struct MatrixStruct_t
{
	int                 width;
	int                 height;
	void				**data;
};

int Matrix_out_of_range(Matrix mat, int x, int y);

Matrix Matrix_init(int width, int height) {
	int size = width * height;
	Matrix matrix;

	if ((matrix = (Matrix)malloc(sizeof(struct MatrixStruct_t))) == NULL)
		return NULL;

	matrix->width = width;
	matrix->height = height;
	if ((matrix->data = malloc(sizeof(void*) * size)) == NULL)
		return NULL;

	Matrix_clear(matrix);

	return matrix;
}

void Matrix_destroy(Matrix mat) {
	int i;
	for (i = 0; i < (mat->height * mat->width); i++){
		if(mat->data[i] != NULL)
			free(mat->data[i]);
	}

	free(mat->data);
	free(mat);
}

void Matrix_clear(Matrix mat) {
	int size = mat->height * mat->width;
	int i;
	for (i = 0; i < size; i++)
		mat->data[i] = NULL;
}

int Matrix_get_width(Matrix mat) {
	return mat->width;
}

int Matrix_get_height(Matrix mat) {
	return mat->height;
}

int Matrix_get(Matrix mat, int x, int y, void **data) {
	int i = (x * Matrix_get_height(mat)) + y;

	if (Matrix_out_of_range(mat, x, y)) {
		return -1;
	}

	*data = mat->data[i];
	return 0;
}

int Matrix_set(Matrix mat, int x, int y, void *data) {
	int i = (x * Matrix_get_height(mat)) + y;

	if (Matrix_out_of_range(mat, x, y)){
		return -1;
	}

	mat->data[i] = data;
	return 0;
}

int Matrix_remove(Matrix mat, int x, int y, void **data) {
	int ret = Matrix_get(mat, x, y, data);

	if (ret >= 0) {
		Matrix_set(mat, x, y, NULL);
	}

	return ret;
}

/*
* Support functions
*/

int Matrix_out_of_range(Matrix mat, int x, int y) {
	return x < 0 || x > mat->width || y < 0 || y > mat->height;
}
