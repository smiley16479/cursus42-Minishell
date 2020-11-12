#include "include.h"

void ft_exec(char *bin_path, char **av, char **envp)
{
	if (execve(bin_path, av, envp))
		write(1, "ERROR\n", 6);

}

void endless_prog(void)
{
	printf("end_less_prog..\n");
	while (1)
		sleep(5);
}

void handler(int i)
{
	printf("sig_child : %d\n", i);
	exit(130);
}
void handler1(int i)
{
	printf("sig_parent : %d\n", i);
}

void	signal_set_up(void (*ft_handler)(int))
{
	signal(SIGINT, *ft_handler);
	// signal(SIGQUIT, *ft_handler);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int wstatus = 0;
	pid_t pid = fork();
	if (!pid)
	{
		signal_set_up(handler);
		endless_prog();
		// ft_exec("endless", av, NULL); //endless est un while(1);
	}
	else
	{
		signal_set_up(handler1);
		waitpid(pid, &wstatus, 0);
	}
	printf("in main for pid : %d et wstatus %d\n", pid, wstatus >> 8);
	return 0;
}
