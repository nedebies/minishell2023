/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:50:20 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/20 09:22:48 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_comp(char *one, char *two)
{
	int	i;

	i = 0;
	while (one && two)
	{
		if (one[i] > two[i])
			return (1);
		else if (one[i] < two[i])
			return (0);
		else if (one[i] == two[i])
			i++;
	}
	return (0);
}

static void	ft_bubble_sort(t_env **is_envp_list, int nbr)
{
	t_env	*ls_tmp;
	int		swapped;
	int		i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < nbr - 1)
		{
			if (ft_comp(is_envp_list[i]->name, is_envp_list[i + 1]->name))
			{
				ls_tmp = is_envp_list[i];
				is_envp_list[i] = is_envp_list[i + 1];
				is_envp_list[i + 1] = ls_tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

t_env	**ft_sortenv(t_list **is_envp_list)
{
	t_env	**ls_envp_list;
	t_list	*ls_cur_env;
	int		i;

	i = 0;
	ls_envp_list = calloc(ft_lstsize(*is_envp_list) + 1, sizeof(t_env *));
	if (!ls_envp_list)
		return (0);
	ls_cur_env = *is_envp_list;
	while (ls_cur_env)
	{
		ls_envp_list[i] = (t_env *)(ls_cur_env->content);
		i++;
		ls_cur_env = ls_cur_env->next;
	}
	ls_envp_list[i] = NULL;
	ft_bubble_sort(ls_envp_list, ft_lstsize(*is_envp_list));
	return (ls_envp_list);
}
