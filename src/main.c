/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by lkoc              #+#    #+#             */
/*   Updated: 2024/09/08 10:24:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    if (ac == 5)
    {
        ft_putstr_fd("hello", 1);
    }
    else if (ac == 6)
    {
        
    }
    else
    {
        ft_putstr_fd("wrong input", 1);
        free();
        return (0);
    }
    return (0);
}

// void	wypis(char *str, char *info)
// {
// 	if (str)
// 	{
// 		ft_putstr_fd(info, 1);
// 		ft_putstr_fd("-> ", 1);
// 		ft_putstr_fd(str, 1);
// 		ft_putstr_fd("\n", 1);
// 	}	
// }