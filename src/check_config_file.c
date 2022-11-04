/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:55:44 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 14:08:48 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	check_protocol(char **matrix)
{
	if (is_http(matrix[1]) || is_ping(matrix[1]) || is_dns(matrix[1]))
		return (1);
	else
		return (0);
}

int	check_size(char **matrix)
{
	if (is_http(matrix[1]) && count_columns(matrix) != 6)
		return (0);
	if (is_ping(matrix[1]) && count_columns(matrix) != 4)
		return (0);
	if (is_dns(matrix[1]) && count_columns(matrix) != 5)
		return (0);
	else
		return (1);
}

int	check_code_time(char **matrix)
{
	if (is_http(matrix[1]) && (!check_is_digit(matrix[4])
			|| !check_is_digit(matrix[5])))
		return (0);
	if (is_ping(matrix[1]) && !check_is_digit(matrix[3]))
		return (0);
	if (is_dns(matrix[1]) && !check_is_digit(matrix[3]))
		return (0);
	else
		return (1);
}

int	check_method(char **matrix)
{
	int		i;
	char	**methods;

	i = 0;
	if (ft_strncmp_eq(matrix[1], "HTTP", 4))
	{
		methods = methods_array();
		while (methods[i])
		{
			if (ft_strncmp_eq(matrix[3], methods[i], ft_strlen(methods[i])))
			{
				ft_matrix_free(methods);
				return (1);
			}
			i++;
		}
		ft_matrix_free(methods);
		return (0);
	}
	return (1);
}

int	check_config_line(char *config_line, t_data *data)
{
	char	**matrix;

	matrix = ft_split2(config_line, '\t');
	if ((!check_protocol(matrix)) || (!check_size(matrix))
		|| (!check_code_time(matrix)) || (!check_method(matrix)))
	{
		fprintf(stderr, "Configuration file error\n");
		ft_matrix_free(matrix);
		free(data->file_info);
		return (0);
	}
	ft_matrix_free(matrix);
	return (1);
}
