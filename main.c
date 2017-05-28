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

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "mines.h"
#include "matrix.h"

void read_stdin_int(int *val, char *msg, int neg)
{
	char c;
	int i = INT_MIN;

	if (msg != NULL)
		printf("%s", msg);

	do
	{
		printf(">");
		scanf("%d", &i);
		while ((c = getchar()) != '\n' && c != EOF) {}
	} while (i == INT_MIN && !neg && i < 0);

	*val = i;
}

int print_matrix(Mine game)
{
	char c;
	int i, j, width, height, shown;
	MineNode node;

	width = Mine_get_width(game);
	height = Mine_get_height(game);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (Mine_get(game, j, i, &node) == CODE_OK)
			{
				c = ' ';
				if (node != NULL && (shown = Mine_is_node_shown(node)) != MARK_HIDDEN)
				{
					if (shown == MARK_FLAG)
					{
						c = 'F';
					}
					else if (Mine_is_node_bomb(node))
					{
						c = 'B';
					}
					else
					{
						c = '0' + Mine_is_node_weight(node);
					}
				}
				printf("[%c]", c);
			}
		}
		printf("\n");
	}

	return 0;
}

int load_schematic(char *f_name, Mine *game)
{
	char buffer[256];
	int x, y, counter;
	FILE *file;

	printf("Load schematic\n");
	if (f_name == NULL)
	{
		printf("Enter schematic file name:\n");
		printf(">");
		fgets(buffer, sizeof(buffer), stdin);
		strtok(buffer, "\n");

		if (strcmp(buffer, "\n") == 0) {
			return 1;
		}
	}
	else
	{
		strcpy(buffer, f_name);
	}

	printf("Opening file: %s.\n", buffer);
	if ((file = fopen(buffer, "r")))
	{
		printf("File opened: %s\n", buffer);
		counter = 0;

		while (!feof(file))
		{
			if (fscanf(file, "%d,%d", &x, &y))
			{
				if (counter == 0)
				{
					if ((*game = Mine_init(x, y)) == NULL)
					{
						printf("Error creating game \n");
						return 1;
					}
				}
				else
				{
					Mine_add_bomb(*game, x, y);
				}
			}
			counter++;
		}

		fclose(file);
		return 0;
	}

	printf("Can't open file: %s.\n", buffer);
	return 1;
}

int save_schematic(char *f_name, Mine game)
{
	char buffer[256];
	int i, j, width, height, counter;

	MineNode node;
	FILE *file;

	printf("Save schematic\n");
	if (f_name == NULL)
	{
		printf("Enter schematic file name:\n");
		printf(">");
		fgets(buffer, sizeof(buffer), stdin);
		strtok(buffer, "\n");

		if (strcmp(buffer, "\n") == 0)
		{
			return 1;
		}
	}
	else
	{
		strcpy(buffer, f_name);
	}

	printf("Opening file: %s.\n", buffer);
	if ((file = fopen(buffer, "w+")))
	{
		printf("File opened: %s\n", buffer);

		width = Mine_get_width(game);
		height = Mine_get_height(game);

		fprintf(file, "%d,%d\n", width, height);
		counter = 1;
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (Mine_get(game, j, i, &node) >= 0)
				{
					if (node != NULL && Mine_is_node_bomb(node))
					{
						fprintf(file, "%d,%d\n", j, i);
						counter++;
					}
				}
			}
		}

		fclose(file);

		printf("%d lines wrote.\n", counter);
		return 0;
	}

	printf("Can't open file: %s.\n", buffer);
	return 1;
}

int play_game(Mine game)
{
	int code, i, j, k, mode, malus, r_count;

	printf("Inserisci il numero di \"indietro\".\n");
	read_stdin_int(&malus, "(-1) per disattivare il malus, (0) per disattivare l'indietro:\n", 1);
	r_count = 0;

	do
	{
		print_matrix(game);

		do
		{
			printf("Scegli un opzione:\n");
			printf("\t1) Scopri la cella\n");
			printf("\t2) Contrassegna la cella\n");
			printf("\t3) Torna al menu principale\n");

			do
			{
				read_stdin_int(&k, NULL, 0);
			} while (k > 3);

			switch (k - 1)
			{
			case 0: mode = MARK_SHOW;
				break;
			case 1: mode = MARK_FLAG;
				break;
			default:
				return CODE_OK;
				break;
			}

			do
			{
				read_stdin_int(&j, "Inserisci la coordinata X\n", 0);
			} while (j < 1 || j > Mine_get_width(game));

			do
			{
				read_stdin_int(&i, "Inserisci la coordinata Y\n", 0);
			} while (i < 1 || i > Mine_get_height(game));

			code = Mine_pick(game, j - 1, i - 1, mode);

			if (code == CODE_INVALID && mode == MARK_FLAG)
			{
				printf("Hai raggiunto il numero massimo di bandierine\n");
			}
		} while (code == CODE_INVALID);

		if (code == CODE_LOSE)
		{
			print_matrix(game);
			printf("Hai pestato una bomba!\n");

			if ((malus == -1 || r_count < malus)) {
				read_stdin_int(&k, "Vuoi tornare indietro? [0/1]\n", 0);
				if (k)
				{
					r_count++;
					for (k = 0; k < r_count; k++)
					{
						code = Mine_rollback(game);
						if (code == CODE_INVALID)
						{
							break;
						}
					}

					printf("Sei tornato indietro di %d step\n", k);
					code = CODE_OK;
				}
			}
		}
	} while (code == CODE_OK);

	if (code == CODE_WIN)
	{
		printf("You win :)\n");
	}
	else if (code == CODE_LOSE)
	{
		printf("You lose :(\n");
	}

	Mine_clear(game);

	return code;
}

int ask_user_menu(Mine game)
{
	int options[] = { 1, 1, 0, 0, 1 };
	int i = 3;
	printf("Scegli un opzione:\n");
	printf("\t1) Genera lo schema\n");
	printf("\t2) Carica uno schema\n");
	if (game != NULL)
	{
		printf("\t3) Salva lo schema\n");
		printf("\t4) Gioca\n");
		options[2] = 1;
		options[3] = 1;

		i = 5;
	}
	printf("\t%d) Esci\n", i);

	do
	{
		read_stdin_int(&i, NULL, 0);
		if (game == NULL && i > 2) {
			i += 2;
		}
		i--;
	} while (i > 4 || !options[i]);

	return i;
}

int ask_user_schema(int *width, int *height, int *bombs)
{
	printf("Genera lo schema\n");

	do
	{
		read_stdin_int(width, "Scegli il numero delle colonne:\n", 0);
	} while (*width < 1);

	do
	{
		read_stdin_int(height, "Scegli il numero delle righe:\n", 0);
	} while (*height < 1);

	do
	{
		read_stdin_int(bombs, "Scegli il numero delle bombe:\n", 0);
	} while (*bombs < 1);

	return 0;
}

int main(int argc, char *argv[])
{
	int code, i, j, k, l;
	Mine game = NULL;

	srand(time(NULL));

	do
	{
		code = 0;
		i = ask_user_menu(game);

		switch (i)
		{
		case 0:
			if (game != NULL) {
				Mine_destroy(game);
			}
			ask_user_schema(&j, &k, &l);

			game = Mine_init(j, k);
			Mine_process(game, l);
			break;
		case 1:
			if (game != NULL) {
				Mine_destroy(game);
			}
			code = load_schematic(argv[1], &game);
			Mine_process(game, 0);
			break;
		case 2:
			print_matrix(game);
			code = save_schematic(argv[1], game);
			break;
		case 3:
			code = play_game(game);
			Mine_destroy(game);
			game = NULL;
			break;
		default:
			if (game != NULL) {
				Mine_destroy(game);
			}
			return EXIT_SUCCESS;
			break;
		}
	} while (code != CODE_ERROR);

	printf("Error found :(\n");

	if (game != NULL) {
		Mine_destroy(game);
	}

	printf("Press ENTER to terminate\n");
	getchar();
	return EXIT_FAILURE;
}
