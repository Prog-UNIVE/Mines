
#ifndef _MATRIX_H_
#include matrix.h
#endif

struct MatrixStruct_t
{
  u_int                 width;
  u_int                 height;
  void                  *data;
};

/*
 * Init the matrix on dynamic mem, using specified sizes.
 * NOTE: memory is not cleared, so random date is still present.
 */
Matrix Matrix_init(u_int width, u_int height){
  int size = x * y;
  Matrix matrix;

  if ((matrix = (Matrix)malloc(sizeof(struct MatrixStruct_t)))==NULL)
    return NULL;

  matrix->width = width;
  matrix->height = height;
  matrix->data = malloc(size);

  return matrix;
}

/*
 * Destroy the matrix, free the memory.
 */
void Matrix_destroy(Matrix data){
  // TODO - Add implementation here :)
}

/*
 * Clear the matrix.
 * NOTE: Elements are not freed from memory
 */
void Matrix_clear(Matrix data){
  u_int size = data->height * data->width;
  int i;
  for(i = 0; i < size; i++)
    data->data[i] = NULL;
}

/*
 * Return matrix width.
 */
u_int Matrix_get_width(Matrix data){
  return data->width;
}

/*
 * Return matrix height.
 */
u_int Matrix_get_height(Matrix data){
  return data->height;
}

/*
 * Return element on [x, y].
 */
void * Matrix_get(Matrix data, u_int x, u_int y){
  u_int i = (x * get_height(data)) + y;

  if(Matrix_out_of_range(data, x, y))
    return NULL;
  return data->data[i];
}

/*
 * Insert element on [x, y], replace current value.
 */
 bool Matrix_insert(Matrix data, u_int x, u_int y, void *val){
  u_int i = (x * get_height(data)) + y;

  if(Matrix_out_of_range(data, x, y))
    return false;
  }

  data->data[i] = val;
  return true;
}

/*
 * Remove element on [x, y], set cell as NULL.
 */
void* Matrix_remove(Matrix data, u_int x, u_int y){
  void *element = Matrix_get(data, x, y);
  Matrix_insert(data,x, y, NULL);

  return element;
}

/*
 * Support functions
 */

 bool Matrix_out_of_range(Matrix data, u_int x, u_int y){

   return x > data->width || y > data->height;
 }
