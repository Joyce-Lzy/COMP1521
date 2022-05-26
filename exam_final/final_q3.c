// COMP1521 21T2 ... final exam, question 3

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void
cp (char *path_from, char *path_to)
{
	FILE *fr = fopen(path_from, "r");
	FILE *fw = fopen(path_to, "w");
	int c;
	while ((c = fgetc(fr)) != EOF) {
		fputc(c, fw);
	}

	fclose(fr);
	fclose(fw);
}

