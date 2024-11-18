/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:25:10 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/18 22:23:40 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str_array(char **to_free)
{
	int	i ;

	i = -1 ;
	while (to_free && to_free[++i])
		free(to_free[i]);
	free(to_free);
}
