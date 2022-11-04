/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:18:04 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 14:10:57 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	node_http(t_config **ptr, char **matrix)
{
	(*ptr)->method = ft_strdup(matrix[3]);
	(*ptr)->code = ft_strdup(matrix[4]);
	(*ptr)->time = ft_strdup(matrix[5]);
	(*ptr)->dns_server = NULL;
}

void	node_ping(t_config **ptr, char **matrix)
{
	(*ptr)->method = NULL;
	(*ptr)->code = NULL;
	(*ptr)->time = ft_strdup(matrix[3]);
	(*ptr)->dns_server = NULL;
}

void	node_dns(t_config **ptr, char **matrix)
{
	(*ptr)->method = NULL;
	(*ptr)->code = NULL;
	(*ptr)->time = ft_strdup(matrix[3]);
	(*ptr)->dns_server = ft_strdup(matrix[4]);
}
