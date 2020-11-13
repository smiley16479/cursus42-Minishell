#include "include.h"

typedef struct to_remove
{
	int fd;
	int std_in;
} t_app;

t_app gp_;
t_app *g_ = &gp_;

void if_chevron(char **cmds, int *pipe_fd)
{
	int fd;
	char buf[64];

	bzero(buf, 64);
	
	if (**cmds == '>')
		if	((fd = open(*(cmds + 1), O_RDWR | (*((*cmds) + 1) == '>' ?
			O_APPEND : O_TRUNC) | O_CREAT , 00664)) != -1)
			while (write(fd, buf, read(g_->std_in, buf ,64)))
				;
	printf("ds if_chevron\n");
	close(pipe_fd[0]);
	close(fd);
}

int main(void)
{
	g_->std_in = dup(STDOUT_FILENO); // il faut ecrire sur stdOUT et pas IN
	char **cmds;

	if ((cmds = malloc(sizeof(char *) * 6)))
	{
		cmds[0] = "bonjour";
		cmds[1] = ">>";
		cmds[2] = "11";
		cmds[3] = ">";
		cmds[4] = "22";
		cmds[5] = NULL;
	}
	int pipe_fd[2];
	pipe(pipe_fd);
	dup2(pipe_fd[0], g_->std_in);
	write(pipe_fd[1], *cmds, strlen(*cmds));
	close(pipe_fd[1]);

	if_chevron(cmds +1, pipe_fd);
	close(g_->std_in);
	printf("%c\n%c\n", **cmds, *((*cmds) + 1));
	free(cmds);
	return 0;
}
