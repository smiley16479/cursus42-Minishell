#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define ENFANT 0
void print_unicode();
int status = 2;

void ft_execve(char **envp, char **av)
{
        execve("minishell", av, envp);
}

int func(/* int *pip1, int *pip2, */ char **envp)
{
    char *av[1];
    *av = NULL;
// for (char **tmp = av; *tmp; tmp++)
//     printf("%s\n", *tmp);
    int pip1[2], pip2[2];    

    pid_t pid;
    int saved_stdout = dup(1);
	pipe(pip1);
    pid = fork();
    if (pid == ENFANT)
    {
        close(pip1[1]);
        if ((pip1[0] = dup2(pip1[0] ,STDIN_FILENO)) == -1)
            exit (-1);
        // close(pip1[0]);
        execve("../minishell", av, envp);
    } 
    else
    {
        close(pip1[0]);
        if ((pip1[1] = dup2( pip1[1], STDOUT_FILENO)) == -1)
            exit (-1);
        write(1, "ls a; echo $? ;exit 4\n", 22);
        close(pip1[1]);
        wait(&status);
        status >>= 8;
    }
    dup2(saved_stdout, 1);
    close(saved_stdout);
    return 0;
}


int main(int ac, char **av, char **envp)
{
// for (char **tmp = av; *av && i < 5; tmp++ , i++)
//     printf("%s\n", *tmp);

    // int pip1[2], pip2[2];
     
    func(/* pip1, pip2, */ envp);
    // write(2, "echo hey ; exit\n", 16);
    printf("le status : %d\n", status);
    return (100);
}



/* 
int main(int ac, char **av, char **envp)
{
    int pip;
    int status;

for (char **tmp = av; *tmp; tmp++)
    printf("%s\n", *tmp);
    pid_t pid;
    //execve(const char *filename, char *const argv[], char *const envp[]);
    dup2(0, 1);
    pid = fork();
    if (!pid)
    {
        execve("minishell", av, envp);
        write(0, "ls\n", 3 );
    } 
    else
    {
        // waitpid(pid_t pid, int *wstatus, int options);
        write(0, "ls\n", 3 );
        waitpid(pid, &status, WUNTRACED);
    }
    return 0;
}
 */

void print_unicode()
{

int i = 0;
char *j = (char *)&i;
printf("%p\n", (j + 316));
for (char **tmp = (char**)(j + 316); tmp && i < 5; tmp++, i++)
    printf("%s\n", *tmp);

//    for (char **tmp = av; *av && i < 5; tmp++ , i++)
//     printf("%s\n", *tmp); 
    // setlocale(LC_CTYPE, "");
    // wchar_t emo = 0x1F60A;
    // wprintf(L"%lc\n", emo);
}