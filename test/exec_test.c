#include "include.h"

void ft_exec(char *bin_path, char **av, char **envp)
{
	if (execve(bin_path, av, envp))
		write(1, "ERROR\n", 6);

}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char **cmds;

	if ((cmds = malloc(sizeof(char *) * 6)))
	{
		cmds[0] = "env";
		cmds[1] = "aurevoir=a";
		cmds[2] = NULL;
		cmds[3] = "env";
		cmds[4] = "''";
		cmds[5] = NULL;
	}
    ft_exec("/usr/bin/env", cmds, envp);
    ft_exec("/usr/bin/env", &cmds[4], envp);
	printf("%c\n%c\n", **cmds, *((*cmds) + 1));
	free(cmds);
	return 0;
}
