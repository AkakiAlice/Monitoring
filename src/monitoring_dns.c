/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_dns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 02:28:52 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 12:39:33 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	show_dns_terminal(t_data *data, t_config *node)
{
	ft_printf("================================================\n");
	ft_printf(" name: %s\n", node->name);
	ft_printf(" address: %s\n", node->address);
	ft_printf(" protocol: %s\n", node->protocol);
	ft_printf("%s\n", data->status);
	ft_printf("%s\n", data->time);
	ft_printf("================================================\n\n");
}

void	filter_dns(char *line, t_data *data)
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = ft_split2(line, ';');
	while (matrix[i])
	{
		if (!ft_strncmp(line, ";; Query", 8))
			data->status = matrix[i];
		if (!ft_strncmp(line, ";; WHEN", 7))
			data->time = matrix[i];
		i++;
	}
}

void	monitoring_dns(t_config *node, t_data *data, int fd_log)
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
			execlp("dig", "dig", ft_strcat("@", node->dns_server),
				node->address, "+noall", "+stats", "+answer", NULL);
		}
		close(fd[1]);
		dprintf(fd_log, "%s\n", read_pipe(fd[0], data, node));
		show_dns_terminal(data, node);
		sleep(ft_atoi(node->time));
	}
}
