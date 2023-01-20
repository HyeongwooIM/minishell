//
// Created by jiyun on 2023/01/17.
//

#include "../minishell.h"
#include "./parse.h"

/* parse error 검사
 * lst 생성 및 추가
 * 청크 리스트를 토큰 리스트에 깊은 복사 하면서 cmd 인지 cmd에 딸린 옵션인지.. 확인하고 type 바꿔주기
 */
static void	free_all(char **ret)
{
    size_t	i;

    i = 0;
    while (ret[i] != 0)
    {
        free(ret[i]);
        i++;
    }
    free(ret);
}

char	**ft_strjoin_1to2(char **dest, char *src)
{
	unsigned int	word_num;
	long			i;
	char	**res;

    word_num = 0;
    if (!dest || !*dest)
        res = malloc(sizeof(char *) * 2);
    else
    {
        while (dest[word_num])
            ++word_num;
        res = malloc(sizeof(char *) * (word_num + 2));
    }
	if (!res)
		exit (1); //error
	i = -1;
	while (++i < word_num)
		res[i] = ft_strdup(dest[i]);
	res[word_num] = ft_strdup(src);
	res[word_num + 1] = 0;
	if (dest)
		free_all(dest);
	return (res);
}