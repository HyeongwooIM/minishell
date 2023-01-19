#ifndef EXPORT_H
#define EXPORT_H

#define PATH_MAX = 4096;
#include "../libft/libft.h"
#include <stdio.h>

typedef enum e_rdir_type
{
	RDIR, // > 0 
	R_RDIR, // < 1
	D_RDIR, // >> 2
	HEREDOC // << 3
}	t_rdir_type;

typedef struct s_rdir
{
	int type;
	char *with; //filename or endpoint(heredoc)
	struct s_rdir *next;
}	t_rdir;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct s_cmd
{
	// input: echo 123 123 123 > a > b < c < d (no option)
	char *name; // ex : "cat"
	char **content; // ex : {"123", "123", "123"}
	struct t_rdir *rdir; // rdir->type: RDIR(>), rdir->file: "a", rdir->next->type: RDIR(>), rdir->next->file: "b" ...
	int is_heredoc; // heredoc 여부
	struct s_cmd *next;
}	t_cmd;

typedef struct s_info
{
	struct s_env env_list;
} t_info;

extern struct s_info g_info;

t_info g_info;

t_env *find_env_add(char *key);
t_env *find_env(char *key);
int	ft_strcmp(const char *str1, const char *str2);
char **ft_strjoin2(char *str, char **arr);
void ft_unset(t_cmd *cmd);
void ft_pwd();
void ft_pipe();
void ft_here_doc(t_cmd *cmd);
void ft_export(t_cmd *cmd);
void ft_exit(t_cmd *cmd);
void ft_exe(t_cmd *cmd, t_env *env);
void ft_exe(t_cmd *cmd, t_env *env);
void	ft_echo(t_cmd	*cmd);
void	ft_cd(t_cmd *cmd);
void	execute(t_cmd	*cmd, t_env *env);
int	check_builtin(char *cmd_name);
int	single_builtin(t_cmd *cmd, t_env env);


#endif