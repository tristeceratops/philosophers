/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/05/24 15:03:41 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_putchar(int fd, char *c)
{
    write(1, c, 1);
}

void    ft_putstr(int fd, char *str)
{
    while (*str)
    {
        ft_putchar(1, str);
        str++;
    }
}