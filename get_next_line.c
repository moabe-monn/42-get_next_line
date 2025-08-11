/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabe <moabe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:09:49 by moabe             #+#    #+#             */
/*   Updated: 2025/08/11 11:30:13 by moabe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_getc(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufp;
	static int	n;

	if (n < 0)
		n = 0;
	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		bufp = buf;
		if (n == 0)
			return (EOF);
		else if (n < 0)
		{
			bufp = NULL;
			return (-2);
		}
	}
	n--;
	if (bufp != NULL)
		return ((int)*bufp++);
	return (-2);
}

static int	ft_putc(t_string *tag, char c)
{
	char	*new_str;
	size_t	new_capa;

	if (tag->len + 1 >= tag->capasity)
	{
		if (tag->capasity == 0)
			new_capa = 16;
		else
			new_capa = tag->capasity * 2;
		new_str = (char *)malloc(new_capa);
		if (new_str == NULL)
			return (-1);
		if (tag->str != NULL)
		{
			ft_memcpy(new_str, tag->str, tag->len);
			free(tag->str);
		}
		tag->str = new_str;
		tag->capasity = new_capa;
	}
	tag->str[tag->len] = c;
	tag->len++;
	return (0);
}

static int	read_line(t_string *tag, int fd)
{
	int	c;

	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break ;
		if (c == -2 || ft_putc(tag, c) == -1)
			return (-1);
		if ((char)c == '\n')
			break ;
	}
	if (tag->len == 0)
		return (-1);
	tag->str[tag->len] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	t_string	ret;
	int			value;

	ret = (t_string){0};
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	value = read_line(&ret, fd);
	if (value == -1)
	{
		free(ret.str);
		return (NULL);
	}
	return (ret.str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("test.txt", O_RDONLY);
// 	// fd = 1;
// 	while (1)
// 	{
// 		str = get_next_line(fd);
// 		printf("line :%s\n", str);
// 		if (str == NULL)
// 			break ;
// 		free(str);
// 	}
// 	close(fd);
// 	return (0);
// }
