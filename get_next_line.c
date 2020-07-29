/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:49:49 by lisanche          #+#    #+#             */
/*   Updated: 2020/01/10 17:51:39 by lisanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*save_line(char *save)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (0);
	}
	if (!(rtn = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1))))
		return (0);
	i++;
	while (save[i])
		rtn[j++] = save[i++];
	rtn[j] = '\0';
	free(save);
	return (rtn);
}

static char	*check_line(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(rtn = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

int			get_next_line(int fd, char **line)
{
	char		*buff;
	char		*save;
	static char	*array[4096];
	int			reader;

	save = array[fd];
	reader = 1;
	if ((fd < 0 || !line || BUFFER_SIZE <= 0) ||
	(!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	while (!has_return(save) && reader != 0)
	{
		if ((reader = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
		buff[reader] = '\0';
		save = join_str(save, buff);
	}
	free(buff);
	*line = check_line(save);
	array[fd] = save_line(save);
	return (reader == 0 && array[fd] == NULL) ? (0) : (1);
}
int        main(void)
{
    char *res = 0;
    int fd = open("text.txt", O_RDONLY);
    int cont;
    while((cont = get_next_line(fd, &res)) > 0)
	{
        printf("%i %s\n",cont, res);
		free(res);
	}
    printf("%i %s\n",cont, res);
	free(res);
	system("leaks a.out");
}