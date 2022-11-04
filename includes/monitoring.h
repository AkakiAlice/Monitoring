/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:52:39 by alida-si          #+#    #+#             */
/*   Updated: 2022/08/03 14:54:48 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H

# include "libft.h"
# include <stdio.h>
# include <curl/curl.h>
# include <sys/wait.h>

typedef struct s_config
{
	char			*name;
	char			*protocol;
	char			*address;
	char			*method;
	char			*code;
	char			*time;
	char			*dns_server;
	struct s_config	*next;
}	t_config;

typedef struct s_data
{
	t_config	*head;
	char		*file_info;
	char		*status;
	char		*time;
}	t_data;

/*	IS_HTTP
**	------------
**	DESCRIPTION
**	Checks if it's the HTTP protocol.
**	PARAMETERS
**	#1. The string referring to the protocol (str);
**	RETURN VALUES
**	Returns 1 if protocol is HTTP, otherwise returns 0
*/
int		is_http(char *str);

/*	IS_PING
**	------------
**	DESCRIPTION
**	Checks if it's the PING protocol.
**	PARAMETERS
**	#1. The string referring to the protocol (str);
**	RETURN VALUES
**	Returns 1 if protocol is PING, otherwise returns 0
*/
int		is_ping(char *str);

/*	IS_DNS
**	------------
**	DESCRIPTION
**	Checks if it's the DNS protocol.
**	PARAMETERS
**	#1. The string referring to the protocol (str);
**	RETURN VALUES
**	Returns 1 if protocol is DNS, otherwise returns 0
*/
int		is_dns(char *str);

/*	CHECK_PROTOCOL
**	------------
**	DESCRIPTION
**	Checks if the protocol in the configuration file
**	is one of the three available.
**	PARAMETERS
**	#1.The array referring to the configuration line (matrix);
**	RETURN VALUES
**	Returns 1 if it is a valid protocol, otherwise returns 0
*/
int		check_protocol(char **matrix);

/*	CHECK_SIZE
**	------------
**	DESCRIPTION
**	Checks the number of configuration columns for each protocol.
**	PARAMETERS
**	#1.The array referring to the configuration line (matrix);
**	RETURN VALUES
**	Returns 0 if it is an invalid number of columns, otherwise returns 1
*/
int		check_size(char **matrix);

/*	CHECK_CODE_TIME
**	------------
**	DESCRIPTION
**	Checks if the interval setting,and code setting in case of HTTP, is a digit.
**	PARAMETERS
**	#1.The array referring to the configuration line (matrix);
**	RETURN VALUES
**	Returns 0 if it is an invalid digit, otherwise returns 1
*/
int		check_code_time(char **matrix);

/*	CHECK_METHOD
**	------------
**	DESCRIPTION
**	Checks if the interval setting,and code setting in case of HTTP, is a digit.
**	PARAMETERS
**	#1.The array referring to the configuration line (matrix);
**	RETURN VALUES
**	Returns 1 if it is a valid method, otherwise returns 0
*/
int		check_method(char **matrix);

/*	CHECK_CONFIG_FILE
**	------------
**	DESCRIPTION
**	Validates the information present in the configuration file.
**	PARAMETERS
**	#1.The string referring to the configuration line (config_line);
**	#2.The pointer to data struct (data);
**	RETURN VALUES
**	Returns 0 if it is an invalid information, otherwise returns 1
*/
int		check_config_line(char *config_line, t_data *data);

/*	NODE_DNS
**	------------
**	DESCRIPTION
**	Initialize the DNS node.
**	PARAMETERS
**	#1.The pointer to config list (ptr);
**	#2.The pointer to configuration file matrix (matrix);
**	RETURN VALUES
**	-
*/
void	node_dns(t_config **ptr, char **matrix);

/*	NODE_PING
**	------------
**	DESCRIPTION
**	Initialize the PING node.
**	PARAMETERS
**	#1.The pointer to config list (ptr);
**	#2.The pointer to configuration file matrix (matrix);
**	RETURN VALUES
**	-
*/
void	node_ping(t_config **ptr, char **matrix);

/*	NODE_HTTP
**	------------
**	DESCRIPTION
**	Initialize the HTTP node.
**	PARAMETERS
**	#1.The pointer to config list (ptr);
**	#2.The pointer to configuration file matrix (matrix);
**	RETURN VALUES
**	-
*/
void	node_http(t_config **ptr, char **matrix);

/*	INIT_NODE
**	------------
**	DESCRIPTION
**	Initializes each node depending on its protocol.
**	PARAMETERS
**	#1.The pointer to config list (ptr);
**	#2.The pointer to configuration file matrix (matrix);
**	RETURN VALUES
**	-
*/
void	init_node(t_config **ptr, char **matrix);

/*	ADD_CONFIG_LST
**	------------
**	DESCRIPTION
**	Adds a new node in the configuration list.
**	PARAMETERS
**	#1.The pointer to config list (head);
**	#2.The pointer to configuration file information (config_line);
**	RETURN VALUES
**	-
*/
void	add_config_lst(t_config **head, char *config_line);

/*	CREATE_CONFIG_LIST
**	------------
**	DESCRIPTION
**	Creates the configuration list.
**	PARAMETERS
**	#1.The pointer to data struct (data);
**	RETURN VALUES
**	Returns 0 if list creation fails, otherwise returns 1
*/
int		create_config_lst(t_data *data);

/*	FREE_LST
**	------------
**	DESCRIPTION
**	Frees the configuration list.
**	PARAMETERS
**	#1.The pointer to config list (head);
**	RETURN VALUES
**	-
*/
void	free_lst(t_config **head);

/*	FREE_NODE
**	------------
**	DESCRIPTION
**	Frees the configuration list node.
**	PARAMETERS
**	#1.The pointer to config list (head);
**	RETURN VALUES
**	-
*/
void	free_node(t_config **head);

/*	COUNT_LIST
**	------------
**	DESCRIPTION
**	Counts the number of nodes in a singly linked list.
**	PARAMETERS
**	#1.The pointer to config list (node);
**	RETURN VALUES
**	The number of nodes in a list
*/
int		count_list(t_config *node);

/*	SHOW_HTTP_TERMINAL
**	------------
**	DESCRIPTION
**	Prints the http information on terminar.
**	PARAMETERS
**	#1.The pointer to config list (node);
**	#2.The pointer to data (data);
**	RETURN VALUES
**	-
*/
void	show_http_terminal(t_config *node, t_data *data);

/*	FILTER_HTTP
**	------------
**	DESCRIPTION
**	Selects the information to print on terminal.
**	PARAMETERS
**	#1.The pointer to the information (info);
**	#2.The pointer to data (data);
**	RETURN VALUES
**	-
*/
void	filter_http(char *info, t_data *data);

/*	MONITORING_HTTP
**	------------
**	DESCRIPTION
**	Init the HTTP monitoring process.
**	PARAMETERS
**	#1.The pointer to the config list (node);
**	#2.The pointer to data (data);
**	#3.Monitoring.log fd (fd_log);
**	RETURN VALUES
**	-
*/
void	monitoring_http(t_config *node, t_data *data, int fd_log);

/*	READ_CONFIG_FILE
**	------------
**	DESCRIPTION
**	Reads the configuration file with a GNL loop.
**	PARAMETERS
**	#1.The pointer to data (data);
**	RETURN VALUES
**	-
*/
void	read_config_file(t_data *data);

/*	CONFIG_FILE_EXIST
**	------------
**	DESCRIPTION
**	Checks if the configuration file exists.
**	PARAMETERS
**	-
**	RETURN VALUES
**	-
*/
int		config_file_exist(void);

/*	RUN_MONITORING
**	------------
**	DESCRIPTION
**	Calls the monitoring functions inside a fork.
**	PARAMETERS
**	#1.The pointer to the config list (node);
**	#2.The pointer to data (data);
**	RETURN VALUES
**	-
*/
void	run_monitoring(t_config *node, t_data *data);

/*	CONFIGS
**	------------
**	DESCRIPTION
**	Calls the configuration check functions.
**	PARAMETERS
**	#2.The pointer to data (data);
**	RETURN VALUES
**	-
*/
int		configs(t_data *data);

/*	SHOW_DNS_TERMINAL
**	------------
**	DESCRIPTION
**	Prints the dns information on terminar.
**	PARAMETERS
**	#1.The pointer to data (data);
**	#2.The pointer to config list (node);
**	RETURN VALUES
**	-
*/
void	show_dns_terminal(t_data *data, t_config *node);

/*	FILTER_DNS
**	------------
**	DESCRIPTION
**	Selects the information to print on terminal.
**	PARAMETERS
**	#1.The pointer to the line containing the information (line);
**	#2.The pointer to data (data);
**	RETURN VALUES
**	-
*/
void	filter_dns(char *line, t_data *data);

/*	MONITORING_DNS
**	------------
**	DESCRIPTION
**	Init the DNS monitoring process.
**	PARAMETERS
**	#1.The pointer to the config list (node);
**	#2.The pointer to data (data);
**	#3.Monitoring.log fd (fd_log);
**	RETURN VALUES
**	-
*/
void	monitoring_dns(t_config *node, t_data *data, int fd_log);

/*	CREATE_HEADER
**	------------
**	DESCRIPTION
**	Creates the header to .log output.
**	PARAMETERS
**	#1.The pointer to the config list (node);
**	#2.pointer to the information that will be sent to the .log (temp);
**	RETURN VALUES
**	The final information that will be printed
*/
char	*create_header(t_config *node, char *temp);

/*	GET_DATA
**	------------
**	DESCRIPTION
**	Calls the filter functions.
**	PARAMETERS
**	#1.The information that will be sent to .log;
**	#2.Pointer to data struct (data);
**	#3.The pointer to the config list (node);
**	RETURN VALUES
**	-
*/
void	get_data(char *info, t_data *data, t_config *node);

/*	READ_PIPE
**	------------
**	DESCRIPTION
**	Reads information from pipe with a gnl loop.
**	PARAMETERS
**	#1.The pipe fd (fd);
**	#2.Pointer to data struct (data);
**	#3.The pointer to the config list (node);
**	RETURN VALUES
**	-
*/
char	*read_pipe(int fd, t_data *data, t_config *node);

/*	FILTER_PING
**	------------
**	DESCRIPTION
**	Selects the information to print on terminal.
**	PARAMETERS
**	#1.The pointer to the line containing the information (line);
**	#2.The pointer to data (data);
**	RETURN VALUES
**	-
*/
void	filter_ping(char *info, t_data *data);

/*	SHOW_PING_TERMINAL
**	------------
**	DESCRIPTION
**	Prints the ping information on terminar.
**	PARAMETERS
**	#1.The pointer to data (data);
**	#2.The pointer to config list (node);
**	RETURN VALUES
**	-
*/
void	show_ping_terminal(t_data *data, t_config *node);

/*	MONITORING_PING
**	------------
**	DESCRIPTION
**	Init the PING monitoring process.
**	PARAMETERS
**	#1.The pointer to the config list (node);
**	#2.The pointer to data (data);
**	#3.Monitoring.log fd (fd_log);
**	RETURN VALUES
**	-
*/
void	monitoring_ping(t_config *node, t_data *data, int fd_log);

/*	PRINT_DNS_SIMP
**	------------
**	DESCRIPTION
**	Prints dns simplify version.
**	PARAMETERS
**	#1.The pointer to line (line);
**	RETURN VALUES
**	-
*/
void	print_dns_simp(char *line);

/*	PRINT_HTTP_SIMP
**	------------
**	DESCRIPTION
**	Prints http simplify version.
**	PARAMETERS
**	#1.The pointer to line (line);
**	RETURN VALUES
**	-
*/
void	print_http_simp(char *line);

/*	PRINT_SIMP
**	------------
**	DESCRIPTION
**	Prints simplify information.
**	PARAMETERS
**	#1.The pointer to the information (info);
**	RETURN VALUES
**	-
*/
void	print_simp(char *info);

/*	RUN_GNL
**	------------
**	DESCRIPTION
**	Gets the information from .log.
**	PARAMETERS
**	#1.The .log fd (fd);
**	RETURN VALUES
**	-
*/
void	run_gnl(int fd);
int		count_columns(char **matrix);
int		check_is_digit(char *str);
char	**methods_array(void);
void	get_http(t_config *node, t_data *data, int fd_log);
void	read_log_file(void);
void	close_lst(t_data *data);

#endif