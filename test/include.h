#ifndef INCLUDE_TEST_
#define INCLUDE_TEST_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../../libft_extended/libft/libft.h"

void ft_exec(char *bin_path, char **av, char **envp);


#endif