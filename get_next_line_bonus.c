/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitay <yitay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:16:49 by yitay             #+#    #+#             */
/*   Updated: 2023/09/06 22:00:10 by yitay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_it(int fd, char *txt)
{
	char	*tmp;
	int		bytes;

	bytes = 0;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	while (!(ft_strchr (txt, '\n')))
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		tmp[bytes] = '\0';
		txt = ft_strjoin(txt, tmp);
	}
	free (tmp);
	if (bytes == -1)
		return (NULL);
	return (txt);
}

char	*extract_it(char *txt)
{
	int		i;
	char	*line;

	i = 0;
	if (!txt || !txt[i])
		return (NULL);
	while (txt[i] != '\n' && txt[i])
		i++;
	line = malloc (sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (txt[i] != '\n' && txt[i])
	{
		line[i] = txt[i];
		i++;
	}
	if (txt[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*extract_liao(char *txt)
{
	int		i;
	char	*left_over;

	i = 0;
	if (!txt)
		return (NULL);
	while (txt[i] != '\n' && txt[i])
		i++;
	if (!txt[i])
	{
		free (txt);
		return (NULL);
	}
	left_over = malloc(sizeof(char) * (ft_strlen(txt) - i));
	if (!left_over)
	{
		free (left_over);
		return (NULL);
	}
	ft_strcpy (left_over, &txt[i + 1]);
	free (txt);
	return (left_over);
}

char	*get_next_line(int fd)
{
	static char	*txt[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	txt[fd] = read_it (fd, txt[fd]);
	line = extract_it (txt[fd]);
	txt[fd] = extract_liao (txt[fd]);
	return (line);
}

// int main()
// {
// 	int fd = open("hello.txt",O_RDONLY);
// 	char *s;
// 	s = get_next_line(fd);
// 	printf("%d\n",fd);
// 	printf("%s\n", s);
// }