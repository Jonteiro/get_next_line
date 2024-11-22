/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:17:46 by jsilveir          #+#    #+#             */
/*   Updated: 2024/11/22 16:10:50 by jsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i] != '\0')
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}

static char	*process_buffer(char *buffer, char *line)
{
	char	*newline_pos;
	char	*temp;

	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos)
	{
		temp = ft_substr(buffer, 0, newline_pos - buffer + 1);
		if (!temp)
			return (free(temp), free(line), NULL);
		line = ft_strjoin(line, temp);
		free(temp);
		clean_buffer(buffer);
		if (!line)
			return (free(temp), free(line), NULL);
	}
	else
	{
		temp = ft_strjoin(line, buffer);
		free(line);
		if (!temp)
			return (free(temp), NULL);
		line = temp;
		buffer[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;
	int			bytes_read;

	line = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (free(line), NULL);
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
		line = process_buffer(buffer, line);
		// clean_buffer(buffer);
		if (!line || ft_strchr(buffer, '\n'))
			return (line);
	}
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
	while ((line = get_next_line(fd)))
	{
		printf("line - %s", line);
		free(line);
	}
	close(fd);
	return (0);
}
