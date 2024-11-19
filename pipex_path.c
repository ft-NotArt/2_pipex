/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:03:35 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/19 10:04:21 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ ;

static char	**get_all_paths(void)
{
	char	**paths ;
	int		i ;

	paths = NULL ;
	i = 0;
	while (environ[i] && strncmp(environ[i], "PATH=", 5))
		i++;
	if (environ[i])
		paths = ft_split(&environ[i][5], ':');
	return (paths);
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

static bool	check_perm(char *cmd, bool *found_cmd)
{
	bool	perm;

	perm = !access(cmd, F_OK);
	if (perm)
	{
		*found_cmd = true ;
		perm = !access(cmd, X_OK);
	}
	return (perm);
}

// TODO:	think of the error case when using this function
//			if the cmd isn't found in any of the paths, and null is returned
//			set strerror as "command not found" (not an errno)
char	*get_valid_path(char *cmd)
{
	char	**paths ;
	char	*res ;
	int		i ;
	bool	found_cmd ;

	found_cmd = false ;
	paths = get_all_paths();
	i = -1 ;
	while (paths && paths[++i])
	{
		res = get_path_cmd(paths[i], cmd);
		if (check_perm(cmd, &found_cmd))
		{
			free_str_array(paths);
			return (res);
		}
		else
			free (res);
	}
	if (found_cmd)
		errno = EACCES ;
	free_str_array(paths);
	return (NULL);
}
