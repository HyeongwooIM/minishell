//
// Created by jiyun on 2023/01/17.
//

#include "../minishell.h"
#include "./parse.h"

/* parse error 검사
 * lst 생성 및 추가
 * 청크 리스트를 토큰 리스트에 깊은 복사 하면서 cmd 인지 cmd에 딸린 옵션인지.. 확인하고 type 바꿔주기
 */

char	**ft_strjoin1to2(char **dest, char *src)
{
	unsigned int	word_num;
	long			i;
	char	**res;

	word_num = 0;
	while (dest[word_num])
		++word_num;
	res = (char **)malloc(sizeof(char *) * (word_num + 2));
	if (!res)
		return (0); //error
	res[word_num + 1] = ft_strdup(src);
	i = -1;
	while (++i < word_num)
		res[i] = ft_strdup(dest[i]);
	res[word_num + 1] = ft_strdup(src);
	res[word_num + 2] = 0;

	i = 0;
	while (dest[i] != 0)
	{
		free(dest[i]);
		i++;
	}
	free(dest);

	return (res);
}