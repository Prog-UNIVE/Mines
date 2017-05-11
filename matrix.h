// Copyright (c) 2017 by Nicolò Veronese.
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

#include <stdbool.h>

#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct MatrixStruct_t *Matrix;

/*
 * Init the matrix on dynamic mem, using specified sizes.
 * NOTE: memory is not cleared, so random date is still present.
 */
Matrix Matrix_init(u_int width, u_int height);

/*
 * Destroy the matrix, free the memory.
 */
void Matrix_destroy(Matrix data);

/*
 * Clear the matrix.
 */
void Matrix_clear(Matrix data);

/*
 * Return matrix width.
 */
u_int Matrix_get_width(Matrix data);

/*
 * Return matrix height.
 */
u_int Matrix_get_height(Matrix data);

/*
 * Return element on [x, y].
 */
void * Matrix_get(Matrix data, u_int x, u_int y);

/*
 * Insert element on [x, y], replace current value.
 */
bool Matrix_insert(Matrix data, u_int x, u_int y, void *val);

/*
 * Remove element on [x, y], set cell as NULL.
 * return value at [x, y]
 */
void* Matrix_remove(Matrix data, u_int x, u_int y);

#endif
