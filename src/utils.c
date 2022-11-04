/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:52:58 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 14:16:57 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

/*	FREE_NODE
**	------------
**	DESCRIPTION
**	Frees the configuration list node.
**	PARAMETERS
**	#1.The pointer to config list (head);
**	RETURN VALUES
**	-
*/
int	count_columns(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

/*	FREE_NODE
**	------------
**	DESCRIPTION
**	Frees the configuration list node.
**	PARAMETERS
**	#1.The pointer to config list (head);
**	RETURN VALUES
**	-
*/
int	check_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*	FREE_NODE
**	------------
**	DESCRIPTION
**	Frees the configuration list node.
**	PARAMETERS
**	#1.The pointer to config list (head);
**	RETURN VALUES
**	-
*/
char	**methods_array(void)
{
	char	**m;

	m = ft_split2("GET,HEAD", ',');
	return (m);
}

int	count_list(t_config *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

void	close_lst(t_data *data)
{
	free_lst(&data->head);
	free(data->file_info);
}
