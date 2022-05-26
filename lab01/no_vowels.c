//z5271698
#include <stdio.h>
#include <string.h>

#define MAX 256

int main(void) {
    int character = getchar();
    while (character != EOF) {
        if (character != 'a' && character != 'e' && character != 'i' &&
		character != 'o' && character != 'u' && character != 'A' &&
		character != 'E' && character != 'I' && character != 'O' &&
		character != 'U') {
            putchar(character);
        }
        character = getchar();
    }
    return 0;
}
