/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:12:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/14 16:14:17 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_minifree(char **arr, int i)
{
	while (--i >= 0)
		free(arr[i]);
	free(arr);
	return (0);
}

char	**ft_minisplit(char *str)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	arr[0] = ft_substr(str, 0, i);
	if (!arr[0])
		return (ft_minifree(arr, 0));
	i++;
	while (str[i + j])
		j++;
	if (ft_strncmp(arr[0], "OLDPWD", 7))
		arr[1] = ft_substr(str, i, j);
	else
		arr[1] = ft_calloc(1, 1);
	if (!arr[1])
		return (ft_minifree(arr, 1));
	arr[2] = 0;
	return (arr);
}
