#include <stdio.h>
#include <stdlib.h>

int rec(int num) {
	if (num == 1) {
		return num;
	} else if (num % 2 == 0 && num != 1) {
		num = num / 2;
		printf("%d\n", num);
		return rec(num);
	} else {
		num = 3*num + 1;
		printf("%d\n", num);
		return rec(num);
	}
}

int main(int argc, char **argv) {
	if (argc == 1) {
		printf("Usage: %s NUMBER\n", argv[0]);
	} else {
		int num = atoi(argv[1]);
		printf("%d\n", num);
		rec(num);
	}
	return 0;
}
