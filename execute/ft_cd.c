#include "../minishell.h"

// t_env *init_env(char *str)
// {
// 	t_env	*env;
	
// 	env = g_info->env_list;
// 	while (env && env->next)
// 		env = env->next;
// 	env->next = malloc(sizeof(t_env));
// 	if (!env->next)
// 		exit(1);
// 	env = env->next;
// 	env->key = ft_strdup(str);
// 	if (!env->key)
// 		exit(1);
// 	env->value = 0;
// 	env->next = 0;
// 	return (env);
// }

void	edit_pwd(char *cwd)
{
	char *cwd_temp;
	t_env *env_pwd;
	t_env *env_oldpwd;

	env_pwd = find_env_add("PWD");
	env_oldpwd = find_env_add("OLDPWD");
	if (!env_pwd || !env_oldpwd)
		exit(1);
	if (env_oldpwd->value)
		free(env_oldpwd->value);
	env_oldpwd->value = env_pwd->value;
	env_pwd->value = ft_strdup(cwd);
	if (!env_pwd->value)
		exit(1) ; // error
}

void	ft_cd(t_cmd *cmd)
{
	char get_cwd[PATH_MAX];
	char *cd_path;
	char *path;

	if (!cmd)
		exit(1);
	path = *cmd->content;
	if (cmd && cmd->content == 0)
		exit(1); // error
	if (!chdir(path))
		exit(1); // error
	if (!getcwd(get_cwd, PATH_MAX))
		exit(1); // error
	edit_pwd(get_cwd);
}