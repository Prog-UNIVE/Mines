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

#include "mines.h"
#include "stack.h"
#include "queue.h"
#include "matrix.h"

struct MineCell_t
{
	int					x;
	int					y;
	int                 bomb;
	int                 weight;
	int                 shown;
};

struct MineStruct_t
{
	int                 width;
	int                 height;
	int                 bombs;
	int                 flags;
	int                 shown;
	int                 init;
	Matrix				matrix;
	Queue				fill_queue;
	Stack				snapshot_stack_matrix;
};

int Mine_flood_fill(Mine game, MineNode node);
MineNode Mine_generate_node();
int random_int(int min, int max);

Mine Mine_init(int width, int height)
{
	Mine game;

	if ((game = (Mine)malloc(sizeof(struct MineStruct_t))) == NULL)
		return NULL;

	game->width = width;
	game->height = height;
	game->bombs = 0;
	game->flags = 0;
	game->shown = 0;
	game->init = 0;
	game->matrix = Matrix_init(width, height);
	game->fill_queue = QUEUE_init();
	game->snapshot_stack_matrix = STACK_init();

	if (game->matrix == NULL || game->fill_queue == NULL || game->snapshot_stack_matrix == NULL)
		return NULL;

	return game;
}

void Mine_destroy(Mine game)
{
	Matrix matrix;

	Matrix_destroy(game->matrix);
	QUEUE_destroy(game->fill_queue);

	while (STACK_size(game->snapshot_stack_matrix) > 0)
	{
		STACK_pop(game->snapshot_stack_matrix, (void **)&matrix);
		Matrix_destroy(matrix);
	}
	STACK_destroy(game->snapshot_stack_matrix);

	free(game);
}

void Mine_clear(Mine game)
{
	int i, j;
	MineNode node;
	Matrix matrix;

	game->flags = 0;
	game->shown = 0;
	
	QUEUE_destroy(game->fill_queue);
	game->fill_queue = QUEUE_init();

	while (STACK_size(game->snapshot_stack_matrix) > 0)
	{
		STACK_pop(game->snapshot_stack_matrix, (void **)&matrix);
		Matrix_destroy(matrix);
	}	

	for (i = 0; i < game->height; i++)
	{
		for (j = 0; j < game->width; j++)
		{
			Matrix_get(game->matrix, j, i, (void **)&node);
			node->shown = MARK_HIDDEN;
		}
	}
}

int Mine_process(Mine game, int generate)
{
	int i, j, k, weight;
	MineNode node, node_s;
	
	if (game->init)
	{
		return CODE_ERROR;
	}

	if (generate > 0)
	{
		for (i = 0; i < generate;)
		{
			j = random_int(0, game->width);
			k = random_int(0, game->height);

			if (Mine_add_bomb(game, j, k) == CODE_OK)
				i++;
		}
	}

	for (i = 0; i < game->height; i++)
	{
		for (j = 0; j < game->width; j++) 
		{

			Matrix_get(game->matrix, j, i, (void **) &node);

			if (node == NULL && (node = Mine_generate_node()) == NULL)
			{
				printf("Error on malloc Mine node\n");
				return;
			}			

			weight = 0;
			if (!node->bomb)
			{
				for (k = j - 1; k <= j + 1; k++)
				{
					if (Matrix_get(game->matrix, k, i - 1, (void **)&node_s) == CODE_OK && node_s != NULL && node_s->bomb) 
					{
						weight++;
					}
					
					if (Matrix_get(game->matrix, k, i + 1, (void **)&node_s) == CODE_OK && node_s != NULL && node_s->bomb)
					{
						weight++;
					}
				}

				if (Matrix_get(game->matrix, j - 1, i, (void **)&node_s) == CODE_OK && node_s != NULL && node_s->bomb)
				{
					weight++;
				}

				if (Matrix_get(game->matrix, j + 1, i, (void **)&node_s) == CODE_OK && node_s != NULL && node_s->bomb)
				{
					weight++;
				}
			}
			else
			{
				weight = 9;
			}			

			node->x = j;
			node->y = i;
			node->weight = weight;
			node->shown = MARK_HIDDEN;

			Matrix_set(game->matrix, j, i, node);
		}
	}

	game->init = 1;
}

int Mine_get_width(Mine game)
{
	return game->width;
}

int Mine_get_height(Mine game) 
{
	return game->height;
}

int Mine_get_bomb_count(Mine game)
{
	return game->bombs;
}

int Mine_get(Mine game, int x, int y, MineNode *data) 
{
	if (!game->init)
	{
		return CODE_ERROR;
	}
	return Matrix_get(game->matrix, x, y, (void **)data);
}

int Mine_pick(Mine game, int x, int y, int marker)
{
	MineNode node;

	if (!game->init)
	{
		return CODE_ERROR;
	}

	if (Matrix_get(game->matrix, x, y, (void **) &node) != CODE_OK)
	{
		return CODE_ERROR;
	}

	if (marker == MARK_FLAG)
	{
		if (node->shown == MARK_FLAG)
		{
			node->shown = MARK_HIDDEN;
			game->flags -= 1;
		}
		else if (game->flags < game->bombs)
		{
			node->shown = MARK_FLAG;
			game->flags += 1;
		}
		else 
		{
			return CODE_INVALID;
		}
	}
	else if (marker == MARK_SHOW && node->shown == MARK_HIDDEN)
	{	
		Mine_snapshot(game);
		Mine_flood_fill(game, node);

		if (node->bomb)
		{
			return CODE_LOSE;
		}		
	}

	if (game->shown == (game->width * game->height) - game->bombs)
	{
		return CODE_WIN;
	}

	return CODE_OK;
}

int Mine_add_bomb(Mine game, int x, int y) {
	MineNode node = NULL;

	if (game->init)
	{
		return CODE_ERROR;
	}

	if (Matrix_get(game->matrix, x, y, (void **)&node) == CODE_ERROR)
	{
		return CODE_ERROR;
	}

 	if (node == NULL && (node = Mine_generate_node()) == NULL)
	{
			return CODE_ERROR;
	}

	if (!node->bomb)
	{
		node->bomb = 1;
		game->bombs += 1;
	}
	else
	{
		return CODE_INVALID;
	}

	return Matrix_set(game->matrix, x, y, node);
}

int Mine_snapshot(Mine game)
{
	int i, j, *k;
	MineNode node;
	Matrix matrix;

	if (!game->init) 
	{
		return CODE_ERROR;
	}

	if ((matrix = Matrix_init(game->width, game->height)) == NULL) 
	{
		return CODE_ERROR;
	}

	for (i = 0; i < game->height; i++)
	{
		for (j = 0; j < game->width; j++) 
		{
			
			if (Matrix_get(game->matrix, j, i, (void **)&node) == CODE_OK &&
				(k = (int *)malloc(sizeof(int))) != NULL) 
			{
				*k = node->shown;
				Matrix_set(matrix, j, i, k);
			}
		}
	}
	
	return STACK_push(game->snapshot_stack_matrix, matrix);;
}

int Mine_rollback(Mine game)
{
	int i, j, *k, shown;
	MineNode node;
	Matrix matrix;

	if (!game->init) 
	{
		return CODE_ERROR;
	}

	if (STACK_is_empty(game->snapshot_stack_matrix))
	{
		return CODE_INVALID;
	}
	
	if (STACK_pop(game->snapshot_stack_matrix, (void **)&matrix) == CODE_OK)
	{
		shown = 0;
		for (i = 0; i < game->height; i++)
		{
			for (j = 0; j < game->width; j++)
			{				
				if (Matrix_get(game->matrix, j, i, (void **)&node) == CODE_OK &&
					Matrix_get(matrix, j, i, (void **)&k) == CODE_OK)
				{
					if (node->shown == MARK_SHOW)
					{
						node->shown = *k;

						if (node->shown == MARK_SHOW)
						{
							shown++;
						}
					}
				}
				else
				{
					return CODE_ERROR;
				}
			}
		}

		Matrix_destroy(matrix);
		game->shown = shown;

		printf("Shown count: %d\n", shown);

		return CODE_OK;
	}

	return CODE_ERROR;
}

int Mine_flood_fill(Mine game, MineNode first_node)
{
	int x, y, k;
	MineNode node;

	if (QUEUE_enqueue(game->fill_queue, first_node) == CODE_OK) {
		while (QUEUE_size(game->fill_queue) > 0) {
			if (QUEUE_dequeue(game->fill_queue, (void **)&node) != CODE_OK)
			{
				return CODE_ERROR;
			}

			if (node->shown == MARK_HIDDEN) {
				node->shown = MARK_SHOW;
				game->shown++;

				if (node->weight == 0) {
					x = node->x;
					y = node->y;

					for (k = x - 1; k <= x + 1; k++) {
						if (Matrix_get(game->matrix, k, y - 1, (void **)&node) == CODE_OK && node != NULL) {
							QUEUE_enqueue(game->fill_queue, node);
						}

						if (Matrix_get(game->matrix, k, y + 1, (void **)&node) == CODE_OK && node != NULL) {
							QUEUE_enqueue(game->fill_queue, node);
						}
					}

					if (Matrix_get(game->matrix, x - 1, y, (void **)&node) == CODE_OK && node != NULL) {
						QUEUE_enqueue(game->fill_queue, node);
					}

					if (Matrix_get(game->matrix, x + 1, y, (void **)&node) == CODE_OK && node != NULL) {
						QUEUE_enqueue(game->fill_queue, node);
					}



					/*if (Matrix_get(game->matrix, x, y - 1, (void **)&node) == CODE_OK) {
						QUEUE_enqueue(game->fill_queue, node);
					}

					if (Matrix_get(game->matrix, x, y + 1, (void **)&node) == CODE_OK) {
						QUEUE_enqueue(game->fill_queue, node);
					}

					if (Matrix_get(game->matrix, x - 1, y, (void **)&node) == CODE_OK) {
						QUEUE_enqueue(game->fill_queue, node);
					}

					if (Matrix_get(game->matrix, x + 1, y, (void **)&node) == CODE_OK) {
						QUEUE_enqueue(game->fill_queue, node);
					}*/
				}
			}
		}

		return CODE_OK;
	}

	return CODE_ERROR;
}

MineNode Mine_generate_node()
{
	MineNode node;

	if ((node = (MineNode)malloc(sizeof(struct MineCell_t))) == NULL) 
	{
		return NULL;
	}

	node->x = -1;
	node->y = -1;

	node->bomb = 0;
	node->weight = 0;
	node->shown = MARK_HIDDEN;

	return node;
}

int Mine_is_node_bomb(MineNode node) 
{
	return node->bomb;
}

int Mine_is_node_shown(MineNode node)
{
	return node->shown;
}

int Mine_is_node_weight(MineNode node)
{
	return node->weight;
}

int random_int(int min, int max)
{
	return min + rand() % (max - min);
}
