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
	Matrix				matrix;
	Queue				fill_queue;
	Stack				snapshot_stack;
};

Mine Mine_init(int width, int height, int bombs) {
	int *pi;

	Mine game;

	if ((game = (Mine)malloc(sizeof(struct MineStruct_t))) == NULL)
		return NULL;	

	game->width = width;
	game->height = height;
	game->bombs = bombs;
	game->matrix = Matrix_init(width, height);
	game->fill_queue = QUEUE_init();
	game->snapshot_stack = Stack_init();

	if (game->matrix == NULL || game->fill_queue == NULL || game->snapshot_stack == NULL)
		return NULL;

	return game;
}

void Mine_destroy(Mine game) {
	Matrix *ptr;
	Matrix_destroy(game->matrix);
	Queue_destroy(game->fill_queue);

	while (STACK_size(game->snapshot_stack) > 0) {
		STACK_pop(game->snapshot_stack, (void **)&ptr);
		Matrix_destroy(*ptr);
	}
	Stack_destroy(game->snapshot_stack);

	free(game);
}

void Mine_clear(Mine game) {
	Matrix *ptr;

	game->bombs = 0;

	Matrix_clear(game->matrix);
	Queue_destroy(game->matrix);
	game->fill_queue = QUEUE_init();

	while (STACK_size(game->snapshot_stack) > 0) {
		STACK_pop(game->snapshot_stack, (void **)&ptr);
		Matrix_destroy(*ptr);
	}	
}

void Mine_process(Mine game, int generate) {
	int i, j, weight;
	MineNode *node;

	if (generate) {
		// TODO - Generate the field by adding bombs to the matrix and shuffle it
	}

	for (i = 0; i < game->width; i++) {
		for (j = 0; j < game->height; j++) {

			Matrix_get(game->matrix, i, j, (void **)&node);

			if (node == NULL && (node = (MineNode *) malloc(sizeof(struct MineCell_t))) == NULL) {
				printf("Error on malloc cells\n");
				return 1;
			}

			(*node)->x = i;
			(*node)->y = j;
			(*node)->weight = weight;
			
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
	return Matrix_get(game->matrix, x, y, data);
}

int Mine_pick(Mine game, int x, int y, int marked) {
	MineNode *data;

	if (Matrix_get(game->matrix, x, y, (void **) &data) != CODE_OK) {
		return -1;
	}
	(*data)->shown = marked;

	// TODO - open additional cells if the current one has waight = 0, if is bomb return 1;

	if ((*data)->weight == 0) {
		// TODO - Color fill algorythm
	}

	if ((*data)->bomb) {
		return 1;
	}

	return 0;
}

int Mine_add_bomb(Mine game, int x, int y) {
	MineNode *node;

	Matrix_get(game->matrix, x, y, (void **)&node);

	if (node == NULL && (node = (MineNode *)malloc(sizeof(struct MineCell_t))) == NULL) {
		printf("Error on malloc cells\n");
		return 1;
	}

	(*node)->bomb = 1;

	Matrix_set(game->matrix, x, y, node);
}

int Mine_snapshot(Mine game) {
	// TODO - Do memory copy of this
	STACK_push(game->snapshot_stack, &game->matrix);
}

int Mine_rollback(Mine game) {
	Matrix *ptr;
	STACK_pop(game->snapshot_stack, (void **) &ptr);

	game->matrix = *ptr;
}

