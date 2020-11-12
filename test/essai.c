#include "include.h"

#define EXIT 10
#define STAY 11
char **g_envv;
int	ft_error(char *proc, char *mess, char *command, int out)
{
	write(2, proc, strlen(proc));
	write(2, ": ", 2);
	write(2, mess, strlen(mess));
	write(2, ": ", 2);
	write(2, command, strlen(command));
	write(2, "\n", 1);
	if (out == EXIT)
		exit(4);
	return (0);
}
////////////////////////////////////////////////
void	ft_execve(char *file)
{
    char *arg = "-l";
    char *argv[3];
    argv[0] = "ls";
    argv[1] = "''";
    argv[2] = NULL;
	if (execve(file, argv, g_envv) == -1)
	{
		ft_error("minishell", strerror(errno), arg, STAY);
		exit(3);
	}
}

/*
**recherche un exécutable dans tous les dossiers mentionnés par Path
**puis dans le dossier présent
*/

int		ft_parse_exec(char *exec)
{
	char		*file = "/bin/ls";
	struct stat	filestat;

	if (lstat(file, &filestat) == 0)
		ft_execve(file);

	if ((lstat(exec, &filestat)) == 0)
		ft_execve(exec);

	ft_error("minishell", strerror(errno), exec, STAY);
	exit(2);
	return (1);
}

/*
**déclenche parse_exec
*/

/* int		main(int ac, char** av, char **env)
{
    g_envv = env;
	ft_parse_exec("ls");
	exit(1);
	return (55);
} */

int g_status;

int		main(int ac, char** av, char **env)
{
	(void)ac;
	(void)av;
/* 	pid_t pid;
	pid = fork();

	int newfd = dup(STDOUT_FILENO);
	int fd = open("hey", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	write(fd, "salut", 5);
	if (dup2(fd, newfd) == -1)
		exit(-1);
	// printf("fd = %d et STDOUT_FILENO = %d\n", fd, STDOUT_FILENO);
	if (pid == 0)
		write(newfd, "hello toi", ft_strlen("hello toi"));
	else if (pid < 0)
		write(newfd, "erreur", ft_strlen("erreur"));
	else
		waitpid(pid, &g_status, WUNTRACED);
	 */

    g_envv = env;
    struct stat	filestat;
	char *file = "in.c";
    // ft_execve("/usr/bin/env");
    ft_execve("/bin/ls");

	if (lstat(file, &filestat) == 0)
        write(1, "Hello", 5);
	exit(1);
	return (55);
}
