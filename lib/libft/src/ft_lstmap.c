/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *link;
	t_list *current;
	t_list *new;

	if (!lst || !f)
		return (NULL);
	link = NULL;
	current = lst;
	while (lst)
	{
		new = (*f)(lst);
		if (link)
		{
			current->next = new;
			current = current->next;
		}
		else
		{
			link = new;
			current = link;
		}
		lst = lst->next;
	}
	return (link);
}
