#include "minishell.h"

void	edit_pwd(char *cwd)
{
	char *cwd_temp;
	t_env *env_pwd;
	t_env *env_oldpwd;

	env_pwd = find_env_add("PWD");
	env_oldpwd = find_env_add("OLDPWD");
	if (env_oldpwd->value)
		free(env_oldpwd->value);
	env_oldpwd->value = env_pwd->value;
	env_pwd->value = ft_strdup(cwd);
	if (!env_pwd->value)
		exit(1) ; // error
}

void	ft_cd(t_cmd *cmd)
{
	char get_cwd[1024];
	char *cd_path;
	char *path;

	if (!cmd)
		exit(1);
	path = *cmd->content;
	if (cmd && cmd->content == 0)
		exit(1); // error
	if (chdir(path))
		exit(1); // error
	if (!getcwd(get_cwd, 1024))
		exit(1); // error
	edit_pwd(get_cwd);
}