/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:14:01 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 14:12:57 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	init_node(t_config **ptr, char **matrix)
{
	(*ptr)->name = ft_strdup(matrix[0]);
	(*ptr)->protocol = ft_strdup(matrix[1]);
	(*ptr)->address = ft_strdup(matrix[2]);
	if (is_http(matrix[1]))
		node_http(ptr, matrix);
	if (is_ping(matrix[1]))
		node_ping(ptr, matrix);
	if (is_dns(matrix[1]))
		node_dns(ptr, matrix);
}

void	add_config_lst(t_config **head, char *config_line)
{
	t_config	*ptr;
	t_config	*temp;
	char		**matrix;

	ptr = (t_config *)malloc(sizeof(t_config));
	if (ptr == NULL)
		return ;
	matrix = ft_split2(config_line, '\t');
	init_node(&ptr, matrix);
	if ((*head) == NULL)
	{
		ptr -> next = NULL;
		*head = ptr;
	}
	else
	{
		temp = *head;
		while (temp -> next != NULL)
		{
			temp = temp -> next;
		}
		temp->next = ptr;
		ptr->next = NULL;
	}
	ft_matrix_free(matrix);
}

int	create_config_lst(t_data *data)
{
	char	**matrix;
	int		i;
	int		check;

	i = 1;
	check = 0;
	matrix = ft_split2(data->file_info, '\n');
	while (matrix[i])
	{
		if (!check_config_line(matrix[i], data))
		{
			check = 1;
			break ;
		}
		add_config_lst(&data->head, matrix[i]);
		i++;
	}
	ft_matrix_free(matrix);
	if (check == 1)
	{
		free_lst(&data->head);
		return (0);
	}
	return (1);
}
