#include "mines.h"
#include "matrix.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

int load_scheamtic(char *f_name, Mine *game) {
	char buffer[256];
	int x, y, counter;
	FILE *file;

	if (f_name == NULL) {
		printf("Enter schematic file name:\n");
		printf(">");
		fgets(buffer, sizeof(buffer), stdin);
		strtok(buffer, "\n");

		if(strcmp(buffer, "\n") == 0){
			return 1;
		}
	}
	else {
		strcpy(buffer, f_name);
	}

	printf("Opening file: %s.\n", buffer);
	if ((file = fopen(buffer, "r"))) {
		printf("File opened: %s\n", buffer);
		counter = 0;

		while (!feof(file))
		{
			if (fscanf(file, "%d,%d", &x, &y))
			{
				printf("Line %d, x: %d, y: %d\n", counter, x, y);
			}
			counter++;
		}

		fclose(file);
		return 0;
	}

	printf("Can't open file: %s.\n", buffer);
	return 1;
}

int ask_user_menu() {
	char c;
	int i;
	printf("Scegli un opzione:\n");
	printf("\t1) Genera lo schema\n");
	printf("\t2) Carica uno schema\n");
	printf("\t3) Esci\n");

	do {
		printf(">");
		scanf("%d", &i);
		while ((c = getchar()) != '\n' && c != EOF) {}
	} while (i < 1 || i > 3);

	return i - 1;
}

int main(int argc, char *argv[]) {
	int code, i, j, k;
	Mine game;

	printf("Running....\n");

	if(argc > 1){
		i = argc - 1;
	}else{
		i = ask_user_menu();
	}

	switch (i) {
		case 0:
		printf("Generate schematic\n");
		j = k = 8;
		game = Mine_init(j, k, floor((j*j) / 5));
		break;
		case 1:
		printf("Load schematic\n");
		code = load_scheamtic(argv[1], &game);
		break;
		default:
		return EXIT_SUCCESS;
		break;
	}

	if (code) {
		printf("Error found :(\n");
	}

	printf("Press ENTER to terminate\n");
	getchar();
	return EXIT_SUCCESS;
}

/*int print_matrix(Matrix matrix) {
int i, j, x, y;
MineNode *pi;

x = Matrix_get_width(matrix);
y = Matrix_get_height(matrix);

for (i = 0; i < x; i++) {
for (j = 0; j < y; j++) {
if (Matrix_get(matrix, i, j, (void **)&pi) >= 0) {
if (pi != NULL) {
//printf("%d ", *pi);
}
else {
printf("NULL ");
}
}
}
printf("\n");
}

return 0;
}*/
