/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpechinn <vpechinn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:41:25 by vpechinn          #+#    #+#             */
/*   Updated: 2024/02/22 15:28:30 by vpechinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf, char *str)
{
	int		byte;

	byte = 1;
	while (ft_strchr(str, '\n') == 0 && byte != 0)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte < 0)
		{
			free(buf);
			return (0);
		}
		buf[byte] = '\0';
		if (!str)
			str = ft_substr(buf, 0, byte);
		else
			str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*ft_remainder(char	*str)
{
	char	*rem;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i++;
	rem = ft_substr(str, i, ft_strlen(str));
	free(str);
	return (rem);
}

char	*ft_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	i++;
	line = ft_substr(str, 0, i);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buf;
	static char		*str;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
	{
		free(str);
		str = NULL;
		return (0);
	}
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	str = ft_read(fd, buf, str);
	if (!str || str[0] == '\0')
	{
		free(str);
		str = 0;
		return (NULL);
	}
	line = ft_line(str);
	str = ft_remainder(str);
	return (line);
}

// int main()
// {
// 	int i = 0;
// 	int fd = open("txt.txt", O_RDONLY);
// 	while (i < 1)
// 	{
// 		printf("%s", get_next_line(fd));
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }