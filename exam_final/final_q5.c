// COMP1521 21T2 ... final exam, question 5

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void
print_utf8_count (FILE *file)
{
	unsigned long amount_1_byte = 0;
	unsigned long amount_2_byte = 0;
	unsigned long amount_3_byte = 0;
	unsigned long amount_4_byte = 0;
	
	int code_point;
   	while((code_point = fgetc(file)) != EOF) {
		if (code_point < 0x80) {
			amount_1_byte++;
		} else if (code_point == 0x80) {
			int c2 = fgetc(file);
			if (c2 != EOF && c2 <= 0x80) {
				amount_2_byte++;
			} else {
				int c3 = fgetc(file);
				if (c3 != EOF && c3 <= 0x80) {
					amount_3_byte++;
				} else {
					int c4 = fgetc(file);
					if (c4 != EOF) {
						amount_4_byte++;
					}	
				}	
			}
		}
   	}

	fclose(file);
	printf("1-byte UTF-8 characters: %lu\n", amount_1_byte);
	printf("2-byte UTF-8 characters: %lu\n", amount_2_byte);
	printf("3-byte UTF-8 characters: %lu\n", amount_3_byte);
	printf("4-byte UTF-8 characters: %lu\n", amount_4_byte);
}
