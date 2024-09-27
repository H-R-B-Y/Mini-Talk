/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:33:53 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/27 18:23:24 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_server.h"

void	*zeroit(void *ptr, size_t n)
{
	size_t	index;

	if (!ptr)
		return (0);
	index = 0;
	while (index < n)
		((unsigned char *) ptr)[index++] = (unsigned char ) '\0';
	return (ptr);
}

void	print_new_message(t_chunk *this_chunk)
{
	ft_putchar_fd(this_chunk->word, 1);
	if (this_chunk->next)
		print_new_message(this_chunk->next);
	return ;
}

void	free_message(t_chunk *this_chunk)
{
	if (this_chunk->next)
		free_message(this_chunk->next);
	free(this_chunk);
	return ;
}
