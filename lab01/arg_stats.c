#include <stdio.h>
#include <stdlib.h>

#define MAX 100
int main(int argc, char **argv) {
	if (argc == 1) {
		printf("Usage: %s NUMBER [NUMBER ...]\n", argv[0]);
	} else {
		int min = atoi(argv[1]);
		int max = atoi(argv[1]);
		int sum = atoi(argv[1]);	
		int prod = atoi(argv[1]);
		for(int i = 1; i < argc; i++) {
			int num = atoi(argv[i]);
			if (min > num) {
				min = num; 
			}
			if (max < num) {
				max = num; 
			}
			if (i != 1) {
				sum = sum + num;
				prod = prod * num;
			} 
		}
		int mean = sum / (argc - 1);
		printf("MIN:  %d\n", min);
		printf("MAX:  %d\n", max);
		printf("SUM:  %d\n", sum);
		printf("PROD: %d\n", prod);
		printf("MEAN: %d\n", mean);
	}
	return 0;
}
