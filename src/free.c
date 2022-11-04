/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:20:03 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 14:14:11 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	free_node(t_config **head)
{
	if (ft_strncmp_eq((*head)->protocol, "HTTP", 4))
	{
		free((*head)->method);
		free((*head)->code);
	}
	free((*head)->name);
	free((*head)->protocol);
	free((*head)->address);
	free((*head)->time);
}

void	free_lst(t_config **head)
{
	t_config	*temp;

	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		free_node(head);
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
	*head = NULL;
}
