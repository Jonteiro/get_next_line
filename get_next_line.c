/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:17:46 by jsilveir          #+#    #+#             */
/*   Updated: 2024/11/22 17:28:14 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (*buffer || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
		clean_buffer(buffer);
		if (line[ft_strlen(line) - 1] == '\n' )
			return (line);
	}
	return (line);
}

/* char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	char		*newline_pos;
	char		*temp;
	char		*joined_line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
			{
				if (line[0] != '\0')
					return (line);
				return (free(line), NULL);
			}
			buffer[bytes_read] = '\0';
		}
		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos)
		{
			temp = ft_substr(buffer, 0, newline_pos - buffer + 1);
			joined_line = ft_strjoin(line, temp);
			free(line);
			free(temp);
			line = joined_line;
			clean_buffer(buffer);
			return (line);
		}
		else
		{
			temp = ft_strjoin(line, buffer);
			free(line);
			line = temp;
			buffer[0] = '\0';
		}
	}
} */
/* 
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("textfile.txt", O_RDONLY);
	if (fd <= 0)
	{
		printf("Error opening file\n");
		return (1);
	}
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			printf("line - %s", line);
		free(line);
	}
	close(fd);
	return (0);
} */
