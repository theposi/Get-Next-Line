/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crizapat <crizapat@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:55:19 by crizapat          #+#    #+#             */
/*   Updated: 2024/05/29 09:11:59 by crizapat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @name read_storage
 * This function reads from a file descriptor into a buffer, appending the 
 * content to a storage buffer until a newline character is found or the end 
 * of the file is reached.
 * @param fd The file descriptor to read from.
 * @param rest_storage A pointer to the current storage buffer that holds 
 *        the text of previous reads.
 * @return The updated storage buffer with the newly read text appended. 
 *         Returns NULL if an error occurs or if there is nothing to read.
 */
static char	*read_storage(int fd, char *rest_storage)
{
	char		*buffer;
	char		*tmp;
	ssize_t		bytes_to_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(rest_storage), NULL);
	bytes_to_read = 1;
	while (bytes_to_read > 0)
	{
		if (ft_strchr(rest_storage, '\n'))
			return (free(buffer), rest_storage);
		bytes_to_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_to_read < 0)
			return (free(buffer), free(rest_storage), NULL);
		if (bytes_to_read == 0)
			return (free(buffer), rest_storage);
		buffer[bytes_to_read] = '\0';
		tmp = rest_storage;
		rest_storage = ft_strjoin(rest_storage, buffer);
		free(tmp);
		if (!rest_storage)
			return (free(buffer), NULL);
	}
	return (free(buffer), rest_storage);
}

/**
 * @name split_lines
 * This function extracts the first line from the given storage buffer and 
 * updates the buffer to contain only the remaining text after
 * the extracted line.
 * @param rest_storage A double pointer to the storage buffer. This function 
 *        will modify the buffer to remove the extracted line and
 *        leave the rest.
 * @return The extracted line, including the newline character. Returns NULL 
 *         if there is no line to extract.
 */
static char	*split_lines(char **rest_storage)
{
	char	*final_line;
	char	*position;
	char	*tmp;

	if (!(*rest_storage)[0])
		return (NULL);
	position = ft_strchr(*rest_storage, '\n');
	if (!position)
	{
		tmp = ft_strdup(*rest_storage);
		free(*rest_storage);
		*rest_storage = NULL;
		return (tmp);
	}
	final_line = malloc(sizeof(char) * (position - *rest_storage + 2));
	if (!final_line)
		return (NULL);
	ft_strlcpy(final_line, *rest_storage, position - *rest_storage + 2);
	++position;
	tmp = *rest_storage;
	*rest_storage = ft_strdup(position);
	free(tmp);
	return (final_line);
}

/**
 * @name get_next_line
 * This function reads a line from the given file descriptor. It maintains 
 * static storage buffers for each file descriptor to handle any leftover text.
 * @param fd The file descriptor to read from.
 * @return The next line from the file, including the newline character if it 
 *         is present. Returns NULL if there is no more text to read or if 
 *         an error occurs.
 */

char	*get_next_line(int fd)
{
	static char	*rest_storage = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest_storage = read_storage(fd, rest_storage);
	if (rest_storage == NULL)
		return (NULL);
	line = split_lines(&rest_storage);
	if (line == NULL && rest_storage)
	{
		free(rest_storage);
		rest_storage = NULL;
	}
	return (line);
}

// #include "get_next_line.h"
//
// int main()
// {
// 	int     fd = open("./test/HarryPotter.txt", O_RDONLY);
// 	char*   line;
//
// 	line = get_next_line(fd);
// 	if (line == NULL)
// 		printf("There was an error trying to read te document \n");
// 	while (line)
// 	{
// 		printf("This is the line: %s\n", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
