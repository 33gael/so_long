/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazmat <hazmat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:51:05 by hazmat            #+#    #+#             */
/*   Updated: 2025/10/28 22:09:03 by hazmat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*list;

	if (!lst || !f)
		return ;
	list = lst;
	while (list != NULL)
	{
		f(list->content);
		list = list->next;
	}
}
