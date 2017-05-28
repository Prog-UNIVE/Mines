/**
* Copyright (c) 2017 by Nicolò Veronese.
* All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
**/

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

void Matrix_destroy(Matrix mat)
{
	int i, size = mat->height * mat->width;
	for (i = 0; i < size; i++)
	{
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

int Matrix_get_width(Matrix mat) 
{
	return mat->width;
}

int Matrix_get_height(Matrix mat)
{
	return mat->height;
}

int Matrix_get(Matrix mat, int x, int y, void **data) {
	int i = (x * mat->height) + y;

	if (Matrix_out_of_range(mat, x, y))
	{
		return -1;
	}

	*data = mat->data[i];
	return 0;
}

int Matrix_set(Matrix mat, int x, int y, void *data)
{
	int i = (x * mat->height) + y;

	if (Matrix_out_of_range(mat, x, y))
	{
		return -1;
	}

	mat->data[i] = data;
	return 0;
}

int Matrix_remove(Matrix mat, int x, int y, void **data)
{
	int ret = Matrix_get(mat, x, y, data);

	if (ret >= 0)
	{
		Matrix_set(mat, x, y, NULL);
	}

	return ret;
}

/*
* Support functions
*/

int Matrix_out_of_range(Matrix mat, int x, int y)
{
	return x < 0 || x >= mat->width || y < 0 || y >= mat->height;
}
