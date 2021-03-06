/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:32:16 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 10:30:17 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

size_t	ft_strlen(const char *ch)
{
	size_t	counter;

	counter = 0;
	while (*ch != '\0')
	{
		ch++;
		counter++;
	}
	return (counter);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t	counter;

	counter = 0;
	while (counter < num)
	{
		*(char *)ptr = value;
		counter++;
		ptr++;
	}
	return (ptr -= counter);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr;
	const unsigned char	*ptr1;

	i = 0;
	ptr = dest;
	ptr1 = src;
	if (!dest || !src)
		return (NULL);
	if (dest > src)
	{
		while (0 < n--)
			ptr[n] = ptr1[n];
	}
	else
	{
		while (n > i)
		{
			ptr[i] = ptr1[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = 0;
	if (c < 0 || c > 255)
		return ((char *)s);
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	else if (c == '\0')
	{
		while (*s != '\0')
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (c == *s)
		{
			ret = (char *)s;
			return (ret);
		}
		s++;
	}
	if (!ret)
		return (NULL);
	return (ret);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*temp;
	size_t			res;
	size_t			counter;
	unsigned char	*str;

	res = nmemb * size;
	temp = malloc(nmemb * size);
	str = temp;
	counter = 0;
	if (temp == 0)
		return (temp);
	if (temp)
	{
		while (res > 0)
		{
			str[counter] = '\0';
			counter++;
			res--;
		}
	}
	return (temp);
}
