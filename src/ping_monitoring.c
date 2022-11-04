/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:43:37 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 11:44:42 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	filter_ping(char *info, t_data *data)
{
	char	**matrix;
	char	**matrix_time;
	int		i;

	i = 0;
	matrix = ft_split2(info, ' ');
	while (matrix[i])
	{
		if (!ft_strncmp(matrix[i], "time=", 5))
		{
			matrix_time = ft_split2(matrix[i], '=');
			data->time = matrix_time[1];
		}
		i++;
	}
}

void	show_ping_terminal(t_data *data, t_config *node)
{
	ft_printf("================================================\n");
	ft_printf(" name: %s\n", node->name);
	ft_printf(" address: %s\n", node->address);
	ft_printf(" protocol: %s\n", node->protocol);
	ft_printf(" latency: %s ms\n", data->time);
	ft_printf("================================================\n\n");
}

void	monitoring_ping(t_config *node, t_data *data, int fd_log)
{
	int		fd[2];
	int		pid;

	while (1)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			execlp("ping", "ping", "-c1", node->address, NULL);
		}
		close(fd[1]);
		dprintf(fd_log, "%s\n", read_pipe(fd[0], data, node));
		show_ping_terminal(data, node);
		sleep(ft_atoi(node->time));
	}
}
