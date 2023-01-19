#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//char *cmd; // ex : "ls -al" -> "ls"
//char *cmd_option; // ex : "ls -al" -> "-al"
//struct t_rdir_lst *rdir;

// ls > a > b > c
int main (int argc, char **argv, char **envp)
{
	char	*cmd = "/bin/ls";
	char	*arr[] = {"/bin/ls", "-al", NULL};
	int		fd = 0;
	int		i = 0;
	int		len = 3;
	char	*rdir[] = {">", "a", ">>", "b", NULL};

	while (i <= len)
	{
		if (fd)
			close(fd);
		if (rdir[i][0] == '>' && rdir[i][1] == 0)
		{
			i++;
			fd = open(rdir[i],  O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (rdir[i][0] == '>' && rdir[i][1] == '>')
		{
			i++;
			fd = open(rdir[i],  O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		i++;
	}
	dup2(fd,1);
	execve(cmd, arr, envp);
	return (0);
}
