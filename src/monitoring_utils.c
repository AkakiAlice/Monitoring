/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:29:32 by alida-si          #+#    #+#             */
/*   Updated: 2022/11/04 05:21:55 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

char	*create_header(t_config *node, char *temp)
{
	char	*header;
	char	*aux;

	aux = ft_strcat("============================ ",
			ft_strcat(node->name, " ============================\n"));
	header = ft_strcat(aux, temp);
	return (header);
}

void	get_data(char *info, t_data *data, t_config *node)
{
	char	**matrix;
	int		i;

	matrix = ft_split2(info, '\n');
	while (matrix[i])
	{
		if (is_http(node->protocol))
			filter_http(matrix[i], data);
		if (is_ping(node->protocol))
			filter_ping(matrix[i], data);
		if (is_dns(node->protocol))
			filter_dns(matrix[i], data);
		i++;
	}
}

char	*read_pipe(int fd, t_data *data, t_config *node)
{
	char	*ret;
	char	*temp;
	char	*swap;

	temp = ft_strdup("");
	while (1)
	{
		ret = get_next_line(fd);
		if (ret == NULL)
			break ;
		swap = temp;
		temp = ft_strjoin(swap, ret);
		free(swap);
		free(ret);
	}
	get_data(temp, data, node);
	if (is_http(node->protocol) || is_ping(node->protocol))
	{
		swap = temp;
		temp = ft_strcat("\n", swap);
	}
	return (create_header(node, temp));
}
