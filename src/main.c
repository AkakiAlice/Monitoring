/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:13:08 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 14:15:14 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	read_config_file(t_data *data)
{
	char	*ret;
	char	*swap;
	int		fd;

	fd = open("monitoring.db", O_RDONLY);
	data->file_info = ft_strdup("");
	while (1)
	{
		ret = get_next_line(fd);
		if (ret == NULL)
			break ;
		swap = data->file_info;
		data->file_info = ft_strjoin(swap, ret);
		free(swap);
		free(ret);
	}
	close(fd);
}

int	config_file_exist(void)
{
	if (access("monitoring.db", O_RDONLY) != -1)
		return (1);
	perror("monitoring.db");
	return (0);
}

void	run_monitoring(t_config *node, t_data *data)
{
	int	pid;
	int	fd_log;

	fd_log = open("monitoring.log", O_RDWR | O_CREAT);
	while (node != NULL)
	{
		pid = fork();
		if (pid == 0 && is_http(node->protocol))
			monitoring_http(node, data, fd_log);
		if (pid == 0 && is_ping(node->protocol))
			monitoring_ping(node, data, fd_log);
		if (pid == 0 && is_dns(node->protocol))
			monitoring_dns(node, data, fd_log);
		node = node -> next;
	}
}

int	configs(t_data *data)
{
	if (!config_file_exist())
		return (0);
	read_config_file(data);
	if (!create_config_lst(data))
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		size_lst;
	int		i;

	data.head = NULL;
	if (argc <= 2)
	{
		if (!configs(&data))
			return (1);
		if (argc == 2 && ft_strncmp_eq(argv[1], "--simplify", 10))
			read_log_file();
		else
		{
			i = 0;
			size_lst = count_list(data.head);
			run_monitoring(data.head, &data);
			while (i < size_lst)
			{
				wait(NULL);
				i++;
			}
		}
		close_lst(&data);
	}
	return (0);
}
