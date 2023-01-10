#include "../minishell.h"

void	restore_pwd(char *cwd)
{

}

char *path_copy(char *content)
{
	int	len;
	char *str;

	len = 0;
	while (content[len] != ' ' && content[len])
		len;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (--len > 0)
		str[len] = content[len];
	return (str);
}

void	ft_cd(t_cmd *cmd)
{
	char get_cwd[PATH_MAX];
	char *cd_path;

	if (cmd->content == 0 || cmd->content[1])
		return ; // 에러처리
	cd_path = path_copy(cmd->content);
	if (!chdir(cd_path))
		; // error
	if (!getcwd(get_cwd, 4096))
		; // error
	restore_pwd(get_cwd);
	
}