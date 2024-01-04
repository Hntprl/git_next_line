/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:46:18 by amarouf           #+#    #+#             */
/*   Updated: 2024/01/03 02:45:17 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_editbackup(char *line)
{
	size_t	i;
	char	*backup;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i])
		i ++;
	backup = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!backup)
		return (free(backup), free(line), NULL);
	if (line[i])
		line[i + 1] = '\0';
	return (backup);
}

char	*ft_readline(int fd, char *backup, char *rd)
{
	ssize_t	len;
	char	*tmp;

	while (!ft_strchr(rd, '\n'))
	{
		len = read(fd, rd, BUFFER_SIZE);
		if (len <= 0)
			break ;
		rd[len] = '\0';
		if (backup)
		{
			tmp = backup;
			backup = ft_strjoin(backup, rd);
			free(tmp);
		}
		else
			backup = ft_strdup(rd);
	}
	free(rd);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*rd;
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (free(backup[fd]), backup[fd] = NULL);
	rd = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!rd)
		return (free(backup[fd]), backup[fd] = NULL);
	rd[0] = '\0';
	line = ft_readline(fd, backup[fd], rd);
	if (!line)
		return (NULL);
	backup[fd] = ft_editbackup(line);
	if (!line[0])
		return (free(backup[fd]), free(line), backup[fd] = NULL);
	return (line);
}
// int main ()
// {
// 	int fd = open("text.txt", O_CREAT | O_RDWR, 0777);
// 	int ll = open("text1.txt", O_CREAT | O_RDWR, 0777);
// 	char *p = get_next_line(fd);
// 	char *s = get_next_line(ll);
// 	while (p || s)
// 	{
// 		printf("%s", p);
// 		printf("%s", s);
// 		p = get_next_line(fd);
// 		s = get_next_line(ll);
// 	}
// }