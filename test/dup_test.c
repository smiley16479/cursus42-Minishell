#include "include.h"

int	main(void)
{
	char buf[64];

	// int std_in = dup(STDIN_FILENO);
	int std_in = dup(STDOUT_FILENO);
	while (write(std_in, buf, read(std_in, buf, 64)))
		;
	return (0);
}