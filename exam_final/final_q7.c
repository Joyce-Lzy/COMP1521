// COMP1521 21T2 ... final exam, question 7

#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const mode_t NEW_DIR_MODE = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;

void find_dr(char *tree1, char *tree2, char *pathname);

void
cp_directory (char *dir_from, char *dir_to)
{
	// TODO
	// hint:
	// - `man 3 opendir`
	// - `man 3 readdir`
	// - `man 3 closedir`
	// - `man 2 mkdir
	mkdir(dir_to, NEW_DIR_MODE);
	find_dr(dir_from, dir_to, ".");

}

void find_dr(char *tree1, char *tree2, char *pathname) {
	struct stat s1;
    char pathname1[PATH_MAX + 1];
    char pathname2[PATH_MAX + 1];
    snprintf(pathname1, sizeof pathname1,  "%s/%s", tree1, pathname);
    snprintf(pathname2, sizeof pathname2,  "%s/%s", tree2, pathname);
    int r1 = stat(pathname1, &s1);

	if (r1 == 0 && S_ISREG(s1.st_mode)) {
		FILE *fr = fopen(pathname1, "r");
		FILE *fw = fopen(pathname2, "w");
		int c;
		while ((c = fgetc(fr)) != EOF) {
			fputc(c, fw);
		} 
		fclose(fr);
		fclose(fw);
	}

	char p[2*PATH_MAX + 1];
    if (r1 == 0 && S_ISDIR(s1.st_mode)) {
		mkdir(pathname2, NEW_DIR_MODE);
        DIR *dirp = opendir(pathname1);
        struct dirent *de;
        while ((de = readdir(dirp)) != NULL) {
            if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
                continue;
            }
            snprintf(p, sizeof p,  "%s/%s", pathname, de->d_name);
            find_dr(tree1, tree2, p);
        }
        closedir(dirp);
    }
}