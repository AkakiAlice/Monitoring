/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_log_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 07:38:19 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 12:43:19 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

void	print_dns_simp(char *line)
{
	char	**matrix;

	matrix = ft_split2(line, ';');
	if (!ft_strncmp(line, "; <", 3))
		ft_printf("%s\n", matrix[0]);
	if (!ft_strncmp(line, ";; Query time", 13))
		ft_printf("%s\n", matrix[0]);
	if (!ft_strncmp(line, ";; WHEN", 7))
		ft_printf("%s\n\n", matrix[0]);
	ft_matrix_free(matrix);
}

void	print_http_simp(char *line)
{
	if (!ft_strncmp(line, "HTTP", 4))
		ft_printf(" %s\n", line);
	if (!ft_strncmp(line, "Date:", 5) || !ft_strncmp(line, "date:", 5))
		ft_printf(" %s\n\n", line);
}

void	print_simp(char *info)
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = ft_split2(info, '\n');
	while (matrix[i])
	{
		if (!ft_strncmp(matrix[i], "==", 2))
			ft_printf("%s\n", matrix[i]);
		print_dns_simp(matrix[i]);
		print_http_simp(matrix[i]);
		if (!ft_strncmp(matrix[i], "PING", 4))
			ft_printf(" %s\n %s\n\n", matrix[i], matrix[i + 1]);
		i++;
	}
	ft_matrix_free(matrix);
}

void	run_gnl(int fd)
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
	if (ft_strlen(temp) == 0)
	{
		fprintf(stderr, "Empty log file\n");
		return ;
	}
	print_simp(temp);
	free(temp);
}

void	read_log_file(void)
{
	int	fd_log;

	fd_log = open("monitoring.log", O_RDONLY);
	if (fd_log == -1)
		return ;
	run_gnl(fd_log);
	close(fd_log);
}
