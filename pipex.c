/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:15:37 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/18 21:18:27 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char **environ ;

char	**get_paths()
{
	char **paths ;
	int i = -1;
	while (environ[++i] && strncmp(environ[i], "PATH=", 5)) ;
	if (environ[i])
		paths = ft_split(&environ[i][5], ':') ;
	else
		paths = NULL;
	return (paths);
}