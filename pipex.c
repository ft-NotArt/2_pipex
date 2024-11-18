/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:15:37 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/18 22:24:30 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ ;

char	**get_paths(void)
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

// TODO:	think of the error case when using this function
//			if the cmd isn't found in any of the paths, and null is returned
char	*add_path_to_cmd(char *cmd)
{
	char	**paths ;
	char	*res ;
	int		i ;

	paths = get_paths();
	i = -1 ;
	while (paths && paths[++i])
	{
		res = ft_calloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2, 1);
		ft_strlcpy(res, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(res, "/", ft_strlen(res) + 2);
		ft_strlcat(res, cmd, ft_strlen(res) + ft_strlen(cmd) + 1);
		if (!access(res, F_OK))
		{
			free_str_array(paths);
			return (res);
		}
		else
			free (res);
	}
	free_str_array(paths);
	return (NULL);
}
