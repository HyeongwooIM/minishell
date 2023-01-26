//
// Created by jiyun on 2023/01/09.
//

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

# define FALSE 0
# define TRUE 1

typedef struct s_token	t_token;
typedef struct s_rdir	t_rdir;
typedef struct s_cmd	t_cmd;
typedef struct s_parse	t_parse;

typedef enum e_error
{
	SUCCESS,
	FAIL,
	RESTART,
	SYNTAX_Q,
	SYNTAX_E
}	t_error;

/* utils.c */
int		is_space(char c);
int		just_white_space(char *str);
t_cmd	*init_cmd(void);

/* node.c */
t_token	*new_token(int type, char *word);
t_rdir	*new_rdir(int type, char *with);
void	add_token_node(int type, char *word, t_token **tokens);
void	add_rdir_node(int type, char *with, t_rdir *rdir);

/* utils2.c */
void	free_token_lst(t_token *lst);
void	free_rdir_lst(t_rdir *lst);
void	free_arr2(char **ret);
char	*ft_strjoin_1to1(char *s1, char *s2);
char	**ft_strjoin_1to2(char **dest, char *src, int size);

/* utils3.c */
char	get_delim(char *str);
char	*env_value(char *str);
int		ft_isalnum_underbar(int c);
int		is_env(char c);

/* chunks.c */
int		make_chunk_lst(t_parse *info);

/* replace.c */
void	replace_chunk(t_parse *info);

/* tokens.c */
int		make_token_lst(t_parse *info);

/* cmds.c */
void	make_cmd_lst(t_parse *info, t_cmd **cmds);

#endif
