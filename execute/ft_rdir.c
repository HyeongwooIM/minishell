#include "../minishell.h"

//char *cmd; // ex : "ls -al" -> "ls"
//char *cmd_option; // ex : "ls -al" -> "-al"
//struct t_rdir_lst *rdir;

// ls > a > b > c

	// RDIR, // > 0 
	// R_RDIR, // < 1
	// D_RDIR, // >> 2
	// HEREDOC // << 3
void ft_rdir(t_rdir *rdir)
{
	int in_fd;
	int out_fd;

	in_fd = 0;
	out_fd = 0;
	while (rdir)
	{
		if (rdir->type == RDIR || rdir->type == D_RDIR)  // > or >>
		{
			if (out_fd)
				close(out_fd);
			if (rdir->type == RDIR)
				out_fd = open(rdir->with,O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (rdir->type == D_RDIR)
				out_fd = open(rdir->with,O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (rdir->type == R_RDIR || rdir->type == HEREDOC) // <
		{
			if (in_fd)
				close(in_fd);
			if (rdir->type == R_RDIR)
				in_fd = open(rdir->with, O_RDONLY);
			if (rdir->type == HEREDOC && rdir->here_doc_fd)
				in_fd = rdir->here_doc_fd;
		}
		rdir = rdir->next;
	}

	return ;
}

// int main (int argc, char **argv, char **envp)
// {
// 	char	*cmd = "/bin/ls";
// 	char	*arr[] = {"/bin/ls", "-al", NULL};
// 	int		fd = 0;
// 	int		i = 0;
// 	int		len = 3;
// 	char	*rdir[] = {">", "a", ">>", "b", NULL};

// 	while (i <= len)
// 	{
// 		if (fd)
// 			close(fd);
// 		if (rdir[i][0] == '>' && rdir[i][1] == 0)
// 		{
// 			i++;
// 			fd = open(rdir[i],  O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		}
// 		else if (rdir[i][0] == '>' && rdir[i][1] == '>')
// 		{
// 			i++;
// 			fd = open(rdir[i],  O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		}
// 		i++;
// 	}
// 	dup2(fd,1);
// 	execve(cmd, arr, envp);
// 	return (0);
// }
