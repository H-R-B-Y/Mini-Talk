/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:43:35 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/27 18:33:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_server.h"

static t_sig_sender	*g_client;

t_sig_sender	*get_client(pid_t pid)
{
	t_sig_sender	*index;

	if (!g_client->client_pid)
	{
		g_client->client_pid = pid;
		return (g_client);
	}
	if (g_client->client_pid == pid)
		return (g_client);
	index = g_client;
	while (index)
	{
		if (index->client_pid == pid)
			return (index);
		index = index->next_pid;
	}
	index = create_client(pid);
	last_client(g_client)->next_pid = index;
	return (index);
}

void	handle_high_signal(int sig, siginfo_t *info, void *ucontext)
{
	t_sig_sender	*this_client;
	t_chunk			*this_chunk;

	(void) sig;
	(void) ucontext;
	this_client = get_client(info->si_pid);
	this_chunk = last_chunk(this_client->msg_start);
	if (this_chunk->index >= 8)
	{
		this_chunk->next = create_chunk();
		this_chunk = this_chunk->next;
	}
	this_chunk->word += (1 << this_chunk->index);
	this_chunk->index += 1;
}

void	handle_low_signal(int sig, siginfo_t *info, void *ucontext)
{
	t_sig_sender	*this_client;
	t_chunk			*this_chunk;

	(void) sig;
	(void) ucontext;
	this_client = get_client(info->si_pid);
	this_chunk = last_chunk(this_client->msg_start);
	if (this_chunk->index >= 8)
	{
		this_chunk->next = create_chunk();
		this_chunk = this_chunk->next;
	}
	this_chunk->index += 1;
	if (this_chunk->index >= 8 && this_chunk->word == 0)
		this_client->msg_terminated = 1;
}

void	check_new_message(void)
{
	t_sig_sender	*this_client;

	this_client = g_client;
	while (this_client)
	{
		if (this_client->msg_terminated)
		{
			print_new_message(this_client->msg_start);
			free_message(this_client->msg_start);
			this_client->msg_start = create_chunk();
			this_client->msg_terminated = 0;
			kill(this_client->client_pid, SIGUSR1);
			return ;
		}
		this_client = this_client->next_pid;
	}
}

int	main(void)
{
	struct sigaction	sa_high;
	struct sigaction	sa_low;

	g_client = create_client(0);
	sa_high.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_high.sa_mask);
	sa_high.sa_sigaction = &handle_high_signal;
	sigaction(SIGUSR1, &sa_high, 0);
	sa_low.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_low.sa_mask);
	sa_low.sa_sigaction = &handle_low_signal;
	sigaction(SIGUSR2, &sa_low, 0);
	ft_putstr_fd("Current PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
	{
		check_new_message();
		sleep(1);
	}
}
