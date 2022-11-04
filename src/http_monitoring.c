/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:12:27 by alida-si          #+#    #+#             */
/*   Updated: 2022/11/04 05:19:06 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	show_http_terminal(t_config *node, t_data *data)
{
	ft_printf("================================================\n");
	ft_printf(" name: %s\n", node->name);
	ft_printf(" address: %s\n", node->address);
	ft_printf(" protocol: %s\n",
		ft_strcat(node->protocol, ft_strcat("/", node->method)));
	ft_printf(" expected status: %s\n", node->code);
	ft_printf(" returned status: %s\n %s\n", data->status, data->time);
	ft_printf("================================================\n\n\n");
}

void	filter_http(char *info, t_data *data)
{
	char	**aux;
	char	**a;

	a = ft_split2(info, ':');
	if (!ft_strncmp(info, "HTTP", 4))
	{
		aux = ft_split2(a[0], ' ');
		data->status = ft_strdup(aux[1]);
	}
	if (!ft_strncmp(info, "Date:", 4) || !ft_strncmp(info, "date:", 4))
		data->time = ft_strdup(info);
}

void	monitoring_http(t_config *node, t_data *data, int fd_log)
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
			if (ft_strncmp_eq(node->method, "GET", 3))
				execlp("curl", "curl", node->address, "-si", NULL);
			execlp("curl", "curl", node->address, "-sI", NULL);
		}
		close(fd[1]);
		dprintf(fd_log, "%s\n", read_pipe(fd[0], data, node));
		show_http_terminal(node, data);
		sleep(ft_atoi(node->time));
	}
}
