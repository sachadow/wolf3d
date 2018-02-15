/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:20:11 by sderet            #+#    #+#             */
/*   Updated: 2017/11/17 15:00:26 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*second;
	t_list	*third;

	if (lst == 0)
		return (NULL);
	first = f(lst);
	lst = lst->next;
	third = first;
	while (lst->next != NULL)
	{
		lst = lst->next;
		second = (t_list*)malloc(sizeof(t_list));
		third->next = second;
		second = f(lst);
		third = second;
	}
	return (first);
}
