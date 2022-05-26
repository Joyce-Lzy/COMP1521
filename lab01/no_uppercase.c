//z5271698
#include <stdio.h>
#include <ctype.h>

int swap_case(int character);

int main(void) {
    int character = getchar();
    while (character != EOF) {

        int new_character = swap_case(character);
        putchar(new_character);
        character = getchar();
    }
    return 0;
}

int swap_case(int character) {
    if (character >= 'A' && character <= 'Z') {
        int upper_case = character - 'A';
        return 'a' + upper_case;        
    } else {
        return character;
    }
}