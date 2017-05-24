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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#ifndef _MINE_H_
#define _MINE_H_

#ifndef CODE_OK
#define CODE_OK 0
#endif

#define MARK_HIDDEN 0
#define MARK_SHOW 1
#define MARK_FLAG 2


typedef struct MineCell_t *MineNode;
typedef struct MineStruct_t *Mine;

/*
* Init the matrix on dynamic mem, using specified sizes.
*/
Mine Mine_init(int width, int height, int bombs);

/**
* Destroy the matrix, free the memory.
**/
void Mine_destroy(Mine game);

/*
 * Clear the matrix. Re-Init the game
 */
void Mine_clear(Mine game);

/**
* Process the current matrix, calculate cell danger
* if generate is true the field is generated
**/
void Mine_process(Mine game, int generate);

/*
* Return matrix width.
*/
int Mine_get_width(Mine game);

int Mine_get_height(Mine game);

int Mine_get_bomb_count(Mine game);

int Mine_get(Mine game, int x, int y, MineNode *data);

int Mine_pick(Mine game, int x, int y, int marker);

int Mine_add_bomb(Mine game, int x, int y);

int Mine_snapshot(Mine game);

int Mine_rollback(Mine game);

#endif