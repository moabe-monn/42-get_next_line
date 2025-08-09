/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabe <moabe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:09:49 by moabe             #+#    #+#             */
/*   Updated: 2025/08/09 20:23:42 by moabe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static int	ft_getc(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufp;
	static int	n;

	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		bufp = buf;
	}
	else if (n < 0)
	{
		bufp = NULL;
		return (-2);
	}
	if (--n >= 0)
		return ((unsigned char)*bufp++);
	else
		return (EOF);
}

static int	ft_putc(t_string *tag, char c)
{
	char	*new_str;

	if (tag->len + 1 > tag->capasity)
	{
		new_str = (char *)malloc(tag->capasity * 2);
		if (new_str == NULL)
			return (-1);
		ft_memcpy(new_str, tag->str, tag->len);
		tag->capasity = tag->capasity * 2;
		free(tag->str);
		tag->str = new_str;
	}
	tag->str[tag->len] = c;
	tag->len++;
	return (0);
}

static int	read_line(t_string *tag, int fd)
{
	char		c;

	tag->str = (char *)malloc(16);
	tag->capasity = 16;
	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF || c == -2)
			return (-1);
		if (ft_putc(tag, c) == -1)
		{
			return (-1);
		}
		else if (c == '\n')
			break ;
	}
	if (tag->len > 0)
		ft_putc(tag, '\0');
	return (0);
}

char	*get_next_line(int fd)
{
	t_string	ret;
	int			value;

	ret.str = NULL;
	ret.len = 0;
	ret.capasity = 0;
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

#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;

	// fd = open("test.txt", O_RDONLY);
	fd = 1;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		printf("line :%s", str);
	}
	close(fd);
	return (0);
}
