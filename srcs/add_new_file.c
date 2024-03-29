/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 23:02:23 by smickael          #+#    #+#             */
/*   Updated: 2018/03/30 23:02:26 by smickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_full_path(char path[PATH_MAX], char *name,
		char full_path[PATH_MAX])
{
	int	i;

	i = -1;
	while (path[++i])
		full_path[i] = path[i];
	if (i && i < PATH_MAX)
		if (!(path[0] == '/' && path[1] == '\0'))
			full_path[i++] = '/';
	while (*name && i < PATH_MAX)
		full_path[i++] = *name++;
	if (i < PATH_MAX)
		full_path[i] = '\0';
	else
		errno = ENAMETOOLONG;
	return ((i < PATH_MAX) ? 1 : 0);
}

static t_file	*new_file(char path[PATH_MAX], char *name, t_stat *stat)
{
	t_file	*new;

	if (!(new = (t_file*)ft_memalloc(sizeof(t_file)))
			|| (!(new->name = ft_strdup(name))))
		ls_error(NULL, 2);
	new->mode = stat->st_mode;
	new->st_nlink = stat->st_nlink;
	new->st_uid = stat->st_uid;
	new->st_gid = stat->st_gid;
	new->size = stat->st_size;
	new->st_rdev = stat->st_rdev;
	new->time = stat->st_mtimespec.tv_sec;
	new->ntime = stat->st_mtimespec.tv_nsec;
	new->st_blocks = stat->st_blocks;
	get_full_path(path, name, new->full_path);
	new->next = NULL;
	return (new);
}

int				add_new_file(char path[PATH_MAX], char *name, t_file **lst)
{
	char		full_path[PATH_MAX];
	t_stat		stat;

	if (!(get_full_path(path, name, full_path)))
	{
		ls_error(name, 1);
		return (-1);
	}
	if (lstat(full_path, &stat) == -1)
		return (-1);
	if (!*lst)
		*lst = new_file(path, name, &stat);
	else
	{
		while ((*lst)->next)
			lst = &((*lst)->next);
		(*lst)->next = new_file(path, name, &stat);
	}
	return (1);
}
