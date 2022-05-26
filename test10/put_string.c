#include <stdio.h>

#include "put_string.h"

// print s to stdout with a new line appended using fputc (only)

void put_string(char *s) {
   for (int i = 0; s[i] != '\0'; i++) {
      fputc(s[i], stdout);
   }
   fputc('\n', stdout);
}
