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
	Matrix				matrix;
	Queue				fill_queue;
	Stack				snapshot_stack;
};

int Mine_flood_fill(Mine game,	MineNode *node);
int random_int(int min, int max);

Mine Mine_init(int width, int height, int bombs) {
	Mine game;

	if ((game = (Mine)malloc(sizeof(struct MineStruct_t))) == NULL)
		return NULL;

	game->width = width;
	game->height = height;
	game->bombs = bombs;
	game->flags = 0;
	game->shown = 0;
	game->matrix = Matrix_init(width, height);
	game->fill_queue = QUEUE_init();
	game->snapshot_stack = STACK_init();

	if (game->matrix == NULL || game->fill_queue == NULL || game->snapshot_stack == NULL)
		return NULL;

	return game;
}

void Mine_destroy(Mine game) {
	Matrix *ptr;
	Matrix_destroy(game->matrix);
	QUEUE_destroy(game->fill_queue);

	while (STACK_size(game->snapshot_stack) > 0) {
		STACK_pop(game->snapshot_stack, (void **)&ptr);
		Matrix_destroy(*ptr);
	}
	STACK_destroy(game->snapshot_stack);

	free(game);
}

void Mine_clear(Mine game) {
	Matrix *ptr;

	game->flags = 0;
	game->shown = 0;

	Matrix_clear(game->matrix);
	QUEUE_destroy(game->snapshot_stack);
	game->fill_queue = QUEUE_init();

	while (STACK_size(game->snapshot_stack) > 0) {
		STACK_pop(game->snapshot_stack, (void **)&ptr);
		Matrix_destroy(*ptr);
	}
}

void Mine_process(Mine game, int generate) {
	int i, j, k, weight;
	MineNode *node;

	if (generate) {
		for (i = 0; i < game->bombs;) {
			j = random_int(0, game->width);
			k = random_int(0, game->height);

			if (!Mine_add_bomb(game, j, k))
				i++;
		}
	}

	for (i = 0; i < game->width; i++) {
		for (j = 0; j < game->height; j++) {

			Matrix_get(game->matrix, i, j, (void **)&node);

			if (node == NULL && (node = (MineNode *)malloc(sizeof(struct MineCell_t))) == NULL) {
				printf("Error on malloc cells\n");
				return;
			}

			// TODO - Calculate weight
			weight = 0;

			(*node)->x = i;
			(*node)->y = j;
			(*node)->weight = weight;
			(*node)->shown = MARK_HIDDEN;

			Matrix_set(game->matrix, i, j, node);
		}
	}
}

int Mine_get_width(Mine game) {
	return game->width;
}

int Mine_get_height(Mine game) {
	return game->height;
}

int Mine_get_bomb_count(Mine game) {
	return game->bombs;
}

int Mine_get(Mine game, int x, int y, MineNode *data) {
	return Matrix_get(game->matrix, x, y, (void **) &data);
}

int Mine_pick(Mine game, int x, int y, int marker) {
	MineNode *node;

	if (Matrix_get(game->matrix, x, y, (void **)&node) != CODE_OK) {
		return CODE_ERROR;
	}

	Mine_snapshot(game);

	if (marker == MARK_FLAG) {
		if ((*node)->shown == MARK_FLAG) {
			(*node)->shown = MARK_HIDDEN;
			game->flags--;
		}
		else if (game->flags < game->bombs) {
			(*node)->shown = MARK_FLAG;
			game->flags++;
		}
		else {
			return CODE_INVALID;
		}
	}
	else if (marker == MARK_SHOW) {
		if ((*node)->bomb) {
			return CODE_LOSE;
		}
		Mine_flood_fill(game, node);

		if (game->shown == (game->width * game->height) - game->bombs) {
			return CODE_WIN;
		}
	}

	return CODE_OK;
}

int Mine_add_bomb(Mine game, int x, int y) {
	MineNode *node;

	Matrix_get(game->matrix, x, y, (void **)&node);

	if (node == NULL && (node = (MineNode *)malloc(sizeof(struct MineCell_t))) == NULL) {
		return CODE_ERROR;
	}

	if (!(*node)->bomb) {
		(*node)->bomb = 1;
		return Matrix_set(game->matrix, x, y, node);
	}

	return CODE_INVALID;
}

int Mine_snapshot(Mine game) {
	// TODO - Do memory copy of this
	return STACK_push(game->snapshot_stack, &game->matrix);
}

int Mine_rollback(Mine game) {
	Matrix *ptr;
	if (STACK_pop(game->snapshot_stack, (void **)&ptr) == CODE_OK) {
		game->matrix = *ptr;
		return CODE_OK;
	}

	return CODE_ERROR;
}

int Mine_flood_fill(Mine game, MineNode *first_node) {
	int x, y;
	MineNode *node;

	if (QUEUE_enqueue(game->fill_queue, first_node) == CODE_OK) {
		while (QUEUE_size(game->fill_queue) > 0) {
			if (QUEUE_dequeue(game->fill_queue, (void **)&node) != CODE_OK) {
				return CODE_ERROR;
			}

			(*node)->shown = MARK_SHOW;
			game->shown++;

			if ((*node)->weight == 0) {
				x = (*node)->x;
				y = (*node)->y;

				if (Matrix_get(game->matrix, x, y - 1, (void **)&node) == CODE_OK) {
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
				}
			}
		}

		return CODE_OK;
	}

	return CODE_ERROR;
}

int random_int(int min, int max)
{
	return min + rand() % (max - min);
}
