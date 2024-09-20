/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crizapat <crizapat@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:55:19 by crizapat          #+#    #+#             */
/*   Updated: 2024/05/29 09:12:47 by crizapat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*rest_storage[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest_storage[fd] = read_storage(fd, rest_storage[fd]);
	if (rest_storage[fd] == NULL)
		return (NULL);
	line = split_lines(&rest_storage[fd]);
	if (line == NULL && rest_storage[fd])
	{
		free(rest_storage[fd]);
		rest_storage[fd] = NULL;
	}
	return (line);
}

// int main()
// {
// 	int fd = open("./test/bonus1.txt", O_RDONLY);
// 	int fd2 = open("./test/bonus2.txt", O_RDONLY);
//
// 	char *test1 = get_next_line(fd);
// 	char *test2 = get_next_line(fd2);
//
// 	while (test1 && test2) {
// 		printf("Line: %s", test1);
// 		free(test1);
// 		test1 = get_next_line(fd);
// 		printf("Line: %s", test2);
// 		free(test2);
// 		test2 = get_next_line(fd2);
// 	}
// 	close(fd);
// 	close(fd2);
// 	free(test1);
// 	free(test2);
// 	return (0);
// }
