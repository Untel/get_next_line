/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 23:22:02 by adda-sil          #+#    #+#             */
/*   Updated: 2019/10/25 18:46:44 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_strjoin(char *s1, char *s2, int f)
{
	char	*str;
	int		l1;
	int		l2;

	l1 = 0;
	l2 = 0;
	while (s1 && s1[l1])
		l1++;
	while (s2 && s2[l2])
		l2++;
	if (!(str = (char *)malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	while (s1 && *s1)
		*str++ = *s1++;
	if (f && (s1 - l1))
		free(s1 - l1);
		// ;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = 0;
	return (str - l1 - l2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		slen;
	int		delta;

	slen = 0;
	while (s && s[slen])
		slen++;
	delta = (slen - (start));
	if (delta > 0 && delta <= slen)
		slen = len;
	else if (delta > 0 && delta > slen)
		slen = delta;
	else
		slen = 0;
	if (!(str = (char *)malloc(sizeof(char) * (slen + 1))))
		return (NULL);
	str[slen] = 0;
	while (--slen >= 0)
		str[slen] = s[start + slen];
	return (str);
}

int		read_line(int fd, t_fds *sfd)
{
	int		ret;
	int		i;
	int		j;
	char	buffer[BUFFER_SIZE + 1];

	j = 0;
	while (sfd->data && sfd->data[j] && sfd->data[j] != '\n')
		j++;
	if (sfd->data && (sfd->data[j] == '\n'))
		return (j);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = 0;
		if (!(sfd->data = ft_strjoin(sfd->data, buffer, 1)))
			return (-1);
		i = -1;
		while (++i < ret)
			if (buffer[i] == '\n')
				return (j + i);
		j += ret;
	}
	if (ret == 0 && sfd && sfd->data && sfd->data[j] == 0)
		sfd->eof = 1;
	return (ret == -1 ? -1 : j);
}

t_fds	*get_fd(int fd, t_fds **fnode, int to_delete)
{
	t_fds	*node;
	t_fds	*prev;

	node = *fnode;
	while ((node && !(node->fd == fd)))
		if (!node->next || ((node = node->next) && 0))
		{
			if (!(node->next = (t_fds *)malloc(sizeof(t_fds))))
				return (NULL);
			prev = node;
			node = node->next;
			*node = (t_fds){ .fd = fd, .eof = 0, .next = NULL, .prev = prev };
			if (!(node->data = ft_strjoin("", "", 0)))
				return (NULL);
		}
	if (to_delete)
		free(node->data);
	if (to_delete && !node->prev && ((*fnode = node->next) || 1))
		free(node);
	else if (to_delete && node->prev && ((node->prev->next = node->next) || 1))
		free(node);
	if (fnode && *fnode)
		(*fnode)->prev = NULL;
	return (to_delete ? (node = NULL) : node);
}

int		get_next_line(int fd, char **line)
{
	static t_fds	*fnode = 0;
	t_fds			*s;
	int				idx;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!fnode)
	{
		if (!(fnode = (t_fds *)malloc(sizeof(t_fds))))
			return (-1);
		*fnode = (t_fds){ .fd = fd, .eof = 0, .next = NULL, .prev = NULL };
		if (!(fnode->data = ft_strjoin("", "", 0)))
			return (-1);
	}
	if ((!(s = get_fd(fd, &fnode, 0)) || !line))
		return ((get_fd(fd, &fnode, 1) || 1) * -1);
	idx = read_line(fd, s);
	if (idx == -1 || !(*line = ft_substr(s->data, 0, idx)))
		return ((get_fd(fd, &fnode, 1) || 1) * -1);
	if (s->eof && !get_fd(fd, &fnode, 1))
		return (0);
	if (!(tmp = ft_strjoin(s->data + (idx + 1), "", 0)))
		return ((get_fd(fd, &fnode, 1) || 1) * -1);
	free(s->data);
	s->data = NULL;
	return ((s->data = tmp) && 1);
}
