/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:03:35 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/26 04:17:08 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*local_cmd(char *cmd)
{
	bool	found_cmd ;

	found_cmd = false ;
	if (check_perm(cmd, &found_cmd))
		return (ft_strdup(cmd));
	else
		return (NULL);
}

static char	*get_path_cmd(char *path, char *cmd)
{
	char	*res ;

	res = ft_calloc(ft_strlen(path) + ft_strlen(cmd) + 2, 1);
	ft_strlcpy(res, path, ft_strlen(path) + 1);
	ft_strlcat(res, "/", ft_strlen(res) + 2);
	ft_strlcat(res, cmd, ft_strlen(res) + ft_strlen(cmd) + 1);
	return (res);
}

static char	*non_local_cmd(char *cmd)
{
	char	**paths ;
	int		i ;
	char	*res ;
	bool	found_cmd ;

	found_cmd = false ;
	paths = get_all_paths();
	i = -1 ;
	while (paths && paths[++i])
	{
		res = get_path_cmd(paths[i], cmd);
		if (check_perm(res, &found_cmd))
			return (free_str_array(paths), (res));
		else
			free (res);
	}
	if (found_cmd)
		errno = EACCES ;
	free_str_array(paths);
	return (NULL);
}

static char	*get_valid_path_cmd(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (local_cmd(cmd));
	else
		return (non_local_cmd(cmd));
}

char	**get_cmd_args(char *cmd_args)
{
	char	**res ;
	char	*tmp ;

	res = ft_split(cmd_args, ' ');
	if (!res)
		return (ft_putstr_fd(strerror(errno), STDERR_FILENO), NULL);
	tmp = get_valid_path_cmd(res[0]);
	if (!tmp)
	{
		free_str_array(res);
		return (ft_putstr_fd("Command not found\n", STDERR_FILENO), NULL);
	}
	free(res[0]);
	res[0] = tmp ;
	return (res);
}
