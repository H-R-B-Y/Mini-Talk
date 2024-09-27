/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:32:31 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/27 18:24:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_server.h"

t_chunk	*create_chunk(void)
{
	t_chunk	*this_chunk;

	this_chunk = zeroit(malloc(sizeof(t_chunk)), sizeof(t_chunk));
	if (!this_chunk)
		return (0);
	return (this_chunk);
}

t_chunk	*last_chunk(t_chunk *start)
{
	if (!start)
		return (0);
	while (start->next)
		start = start->next;
	return (start);
}

t_sig_sender	*create_client(pid_t pid)
{
	t_sig_sender	*this_client;

	this_client = zeroit(malloc(sizeof(t_sig_sender)), sizeof(t_sig_sender));
	if (!this_client)
		return (0);
	this_client->msg_start = create_chunk();
	this_client->client_pid = pid;
	return (this_client);
}

t_sig_sender	*last_client(t_sig_sender *start)
{
	if (!start)
		return (0);
	while (start->next_pid)
		start = start->next_pid;
	return (start);
}
