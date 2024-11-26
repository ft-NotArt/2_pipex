/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:25:10 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/26 16:20:05 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ ;

void	free_str_array(char **to_free)
{
	int	i ;

	i = -1 ;
	while (to_free && to_free[++i])
		free(to_free[i]);
	free(to_free);
}

char	**get_all_paths(void)
{
	char	**paths ;
	int		i ;

	paths = NULL ;
	i = 0;
	while (environ[i] && ft_strncmp(environ[i], "PATH=", 5))
		i++;
	if (environ[i])
		paths = ft_split(&environ[i][5], ':');
	return (paths);
}

bool	check_perm(char *cmd, bool *found_cmd)
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

void	double_close(int argc, int cmd_index, int fd[2], int fd_in)
{
	close(fd_in);
	if (cmd_index < (argc - 4))
		close(fd[1]);
}

bool	is_only_space(char *str)
{
	bool	res ;

	res = true ;
	while (*str && res)
	{
		if (!ft_isspace(*str))
			res = false ;
		str++ ;
	}
	return (res);
}
