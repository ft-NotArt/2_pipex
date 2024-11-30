/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:25:10 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/30 05:15:44 by anoteris         ###   ########.fr       */
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
	if (!paths)
	{
		paths = malloc(2 * sizeof(char **));
		paths[0] = ft_strdup(".");
		paths[1] = NULL;
	}
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

void	double_close(t_args *arg, int cmd_index, int fd[2], int fd_in)
{
	close(fd_in);
	if (cmd_index < (arg->c - (4 + arg->here_doc)))
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
