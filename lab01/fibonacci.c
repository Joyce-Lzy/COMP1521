//z5271698
#include <stdio.h>
#include <stdlib.h>

#define SERIES_MAX 46

int find_fibonacci(int n);

int main(void) {
    int num;
    while (scanf("%d", &num) != EOF) {
        if (num <= SERIES_MAX) {
            int new_num = find_fibonacci(num);
            printf("%d\n", new_num);
        }
    }
    return 0;
}

int find_fibonacci(int n) {
    if (n == 1) {
        return 1;
    } else if (n == 0) {
        return 0;
    } else {
        return find_fibonacci(n-2) + find_fibonacci(n-1);
    }
}

        
		
		