/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:54:13 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/25 22:31:07 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_file_reqs(t_file_reqs **reqs)
{
	(*reqs)->no = 0;
	(*reqs)->so = 0;
	(*reqs)->we = 0;
	(*reqs)->ea = 0;
	(*reqs)->f = 0;
	(*reqs)->c = 0;
}

void	handle_escape(t_param_mlx **param)
{
	mlx_close_window((*param)->mlx);
	free_map(&(*param)->map);
	exit(0);
}
