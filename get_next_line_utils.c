/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabe <moabe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:09:45 by moabe             #+#    #+#             */
/*   Updated: 2025/08/10 09:16:13 by moabe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d_cpy;
	const unsigned char	*s_cpy;

	d_cpy = (unsigned char *)dest;
	s_cpy = (const unsigned char *)src;
	while (n--)
	{
		*d_cpy++ = *s_cpy++;
	}
	return (dest);
}

// cc -Wall -Wextra -Werror -D BUFFERSIZE=2
// get_next_line.c get_next_line_utils.c
