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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct MatrixStruct_t *Matrix;

/* INTERFACE FUNCTION DECLARATIONS */
/**
* Initializate the matrix.
*
* @return A reference - to a new, empty matrix - if dynamic memory
* allocation for the ADT was successful - or NULL otherwise. Take really
* good care of this return value, since it will be needed as a parameter in
* subsequent calls - to the majority of other matrix handling functions
* in this matrix function interface - i.e. a sort of "handle" to the matrix.
* @see Matrix_destroy()
**/
Matrix Matrix_init(int width, int height);

/**
* Destroy the matrix.
*
* The matrix is destroyed - that is, all memory occupied by the
* elements is deallocated. This is responsible
* for freeing dynamically allocated element data, when this function
* is called. When all elements and data have been deallocated - the
* matrix header is deallocated, too.
*
* @param[in] mat - a reference to current matrix.
* @return Nothing.
* @see Matrix_init()
**/
void Matrix_destroy(Matrix mat);

/**
* Clear the matrix.
*
* The matrix is cleared - that is, all elements are set to NULL
*
* @param[in] mat - a reference to current matrix.
**/
void Matrix_clear(Matrix mat);

/**
* Get the matrix width.
*
* @param[in] mat - a reference to the current matrix.
*
* @return The width, that is, the number of columns in the matrix.
**/
int Matrix_get_width(Matrix mat);

/**
* Get the matrix height.
*
* @param[in] mat - a reference to the current matrix.
*
* @return The height, that is, the number of rows in the matrix.
**/
int Matrix_get_height(Matrix mat);

/**
* Get the element at the specified location.
*
* When called, the 4th parameter of this function, @a data,
* should reference an (external, user-defined) pointer.
* After the call - this referenced, external pointer has been
* redirected, to point to the data of the element -
* if the call was succesful.
*
* @param[in] mat - reference to current matrix.
* @param[in] x - x coord
* @param[in] y - y coord
* @param[out] data - reference to a pointer. After the call,
* this referenced pointer has been redirected to point to
* the data of the element - if the call was successful.
*
* @return Value 0 - if the call was OK - or
* value -1 otherwise.
**/
int Matrix_get(Matrix mat, int x, int y, void **data);

/**
* Set a new element - at the top specified location in the matrix.
*
* This function set an new element - with a reference to
* its corresponding data, given by parameter @a data - at the
* specified position of the matrix.
*
* @param[in] mat - reference to current matrix
* @param[in] x - x coord
* @param[in] y - y coord
* @param[in] data - reference to data to be stored in the new
* element, which is to be inserted at the location specified (x, y).
*
* @return Value 0 - if everything went OK - or value -1 otherwise.
**/
int Matrix_set(Matrix mat, int x, int y, void *data);

/**
* Remove the element atthe specified location.
*
* When called, the 4th parameter of this function, @a data,
* should reference an (external, user-defined) pointer.
* After the call - this referenced, external pointer has been
* redirected, to point to the data of the removed element -
* if the call was succesful. The caller is responsible for
* the future  of this memory - deallocating it, if needed,
* for example. The node at location (x,y) is set to NULL.
*
* @param[in] mat - reference to current matrix.
* @param[in] x - x coord
* @param[in] y - y coord
* @param[out] data - reference to a pointer. After the call,
* this referenced pointer has been redirected to point to
* the data of the removed element - if the call was
* successful. The caller is responsible for the future  of
* this memory - deallocating it, for example.
*
* @return Value 0 - if the call was OK - or
* value -1 otherwise.
**/
int Matrix_remove(Matrix mat, int x, int y, void **data);

#endif
