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

#include "queue.h"
#include "stack.h"
#include "matrix.h"

#ifndef _MINE_H_
#define _MINE_H_

#ifndef CODE_OK
#define CODE_OK 0
#endif

#ifndef CODE_ERROR
#define CODE_ERROR 1
#endif

#ifndef CODE_INVALID
#define CODE_INVALID 2
#endif

#ifndef CODE_WIN
#define CODE_WIN 3
#endif

#ifndef CODE_LOSE
#define CODE_LOSE 4
#endif

#define MARK_HIDDEN 0
#define MARK_SHOW 1
#define MARK_FLAG 2

typedef struct MineCell_t *MineNode;
typedef struct MineStruct_t *Mine;

/* INTERFACE FUNCTION DECLARATIONS */
/**
* Initializate the game.
*
* @return A reference - to a new game - if dynamic memory
* allocation for the game was successful - or NULL otherwise. Take really
* good care of this return value, since it will be needed as a parameter in
* subsequent calls - to the majority of other game handling functions
* in this game function interface - i.e. a sort of "handle" to the game.
* @see Matrix_destroy()
**/
Mine Mine_init(int width, int height);

/**
* Destroy the game.
*
* The fame is destroyed - that is, all memory occupied by the
* matrix, the queue and the stack is deallocated.
* When all ADTs and data have been deallocated - the
* game header is deallocated, too.
*
* @param[in] game - a reference to current game.
* @return Nothing.
* @see Matrix_init()
**/
void Mine_destroy(Mine game);

/**
* Clear the matrix.
*
* The gamematrix is cleared, all nodes are set to MASK_HIDDEN.
* The queue and the stack are cleared.
*
* @param[in] mat - a reference to current matrix.
**/
void Mine_clear(Mine game);

/**
* Process the current matrix, calculate cell danger
* if generate is true the bombs are added to the field
**/
int Mine_process(Mine game, int generate);

/**
* Get the game matrix width.
*
* @param[in] game - a reference to the current fame.
*
* @return The width, that is, the number of columns in the matrix.
**/
int Mine_get_width(Mine game);

/**
* Get the game matrix height.
*
* @param[in] game - a reference to the current game.
*
* @return The height, that is, the number of rows in the matrix.
**/
int Mine_get_height(Mine game);

/**
* Get the bomb count in the game.
*
* @param[in] game - a reference to the current game.
*
* @return The bomb count in the matrix.
**/
int Mine_get_bomb_count(Mine game);

/**
* Get the node at the specified location.
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
int Mine_get(Mine game, int x, int y, MineNode *data);

/**
* Add a bomb at location (x, y) of the current game.
*
* @param[in] game - a reference to the current game.
* @param[in] x - the x coord.
* @param[in] y - the y coord.
* @param[in] marker - the operation code.
*
* @return Value 0 - if the call was OK - or
* value -1 otherwise.
**/
int Mine_pick(Mine game, int x, int y, int marker);

/**
* Add a bomb at location (x, y) of the current game.
*
* @param[in] game - a reference to the current game.
* @param[in] x - the x coord.
* @param[in] y - the y coord.
*
* @return Value 0 - if the call was OK - or
* value -1 otherwise.
**/
int Mine_add_bomb(Mine game, int x, int y);

/**
* Take a snapshot of the current game
*
* @param[in] game - a reference to the current game.
*
* @return Value 0 - if the call was OK - or
* value -1 otherwise.
**/
int Mine_snapshot(Mine game);

/**
* Rollback to a previous snapshot.
*
* @param[in] game - a reference to the current game.
*
* @return Value 0 - if the call was OK - or
* value -1 otherwise.
**/
int Mine_rollback(Mine game);

/**
* Get if node is a bomb.
*
* @param[in] node - a reference to the current node.
*
* @return If a node is a bomb.
**/
int Mine_is_node_bomb(MineNode node);

/**
* Get the node shown mask.
*
* @param[in] node - a reference to the current node.
*
* @return The show mask of a node.
**/
int Mine_is_node_shown(MineNode node);

/**
* Get the node weight.
*
* @param[in] node - a reference to the current node.
*
* @return The weight of a node.
**/
int Mine_is_node_weight(MineNode node);

#endif
