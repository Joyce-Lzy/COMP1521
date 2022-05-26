// z5271698
#include <stdio.h>
#define MAX 256

int main(int argc, char **argv) {
	//(void) argc, (void) argv; // keep the compiler quiet, should be removed
	printf("Program name: %s\n", argv[0]);
	if (argc == 1) {
		printf("There are no other arguments\n");
	} else {
		printf("There are %d arguments:\n", argc - 1);
		for (int i = 1; i < argc; i++) {
			printf("	Argument %d is \"%s\"\n", i, argv[i]);
		}
	}
	return 0;
}
