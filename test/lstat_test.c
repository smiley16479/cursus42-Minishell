#include "include.h"

/* 
** voir man inode pour les macro S_ISREG etc
*/

int main(void)
{
	struct stat filestat;

	if (lstat("pipe_test.c", &filestat) == 0 && (S_ISREG(filestat.st_mode)))
		perror("si succes");
	else
		perror("si failure");
	return (0);
}