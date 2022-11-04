/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_file_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:15:05 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 14:03:46 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int	is_http(char *str)
{
	if (ft_strncmp_eq(str, "HTTP", 4))
		return (1);
	return (0);
}

int	is_ping(char *str)
{
	if (ft_strncmp_eq(str, "PING", 4))
		return (1);
	return (0);
}

int	is_dns(char *str)
{
	if (ft_strncmp_eq(str, "DNS", 3))
		return (1);
	return (0);
}
