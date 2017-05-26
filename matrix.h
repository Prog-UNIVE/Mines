// Copyright (c) 2017 by Nicol� Veronese.
// All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct MatrixStruct_t *Matrix;

/*
* Init the matrix on dynamic mem, using specified sizes.
*/
Matrix Matrix_init(int width, int height);

/*
* Destroy the matrix, free the memory.
*/
void Matrix_destroy(Matrix mat);

/*
* Clear the matrix.
*/
void Matrix_clear(Matrix mat);

/*
* Return matrix width.
*/
int Matrix_get_width(Matrix mat);

/*
* Return matrix height.
*/
int Matrix_get_height(Matrix mat);

/*
* Return element on [x, y].
*/
int Matrix_get(Matrix mat, int x, int y, void **data);

/*
* Insert element on [x, y], replace current value.
*/
int Matrix_set(Matrix mat, int x, int y, void *data);

/*
* Remove element on [x, y], set cell as NULL.
* return value at [x, y]
*/
int Matrix_remove(Matrix mat, int x, int y, void **data);

#endif
