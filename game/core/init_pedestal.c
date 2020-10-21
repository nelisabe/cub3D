/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b_pedestal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:13:05 by nelisabe          #+#    #+#             */
/*   Updated: 2020/10/21 16:13:10 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pedestal(t_core *game, t_object *pedestal)
{
	pedestal->pos[0].volume = 0;
	pedestal->pos[0].a_tmp = 0;
	pedestal->pos[0].a_speed = 8;
	pedestal->pos[0].type = 'p';
	pedestal->pos[0].scale_x = 0.4;
	pedestal->pos[0].scale_y = 0.6;
	set_spr(&pedestal->pos[0], 8.2, 2.6, 0.22);
	place_on_map(game, 8.6, 2.6, pedestal->pos[0].type);
	pedestal->pos[1].volume = 0;
	pedestal->pos[1].a_tmp = 0;
	pedestal->pos[1].a_speed = 8;
	pedestal->pos[1].type = 'p';
	pedestal->pos[1].scale_x = 0.4;
	pedestal->pos[1].scale_y = 0.6;
	set_spr(&pedestal->pos[1], 7.8, 2.6, 0.22);
	place_on_map(game, 7.6, 2.6, pedestal->pos[1].type);
}

void	init_pedestal(t_core *game, char *path)
{
	int		temp;
	int		quantity;

	temp = -1;
	quantity = 1;
	if (!(game->pedestal.tex = (t_tex*)malloc(sizeof(t_tex) * (quantity + 1))))
		error_malloc(game);
	while (++temp < quantity)
		load_image(game, &game->pedestal.tex[temp], \
			ft_strjoin(path, ft_strjoin(ft_itoa(temp), ".xpm")));
	game->pedestal.tex[temp].img.image = NULL;
	game->pedestal.quantity = 2;
	if (!(game->pedestal.pos = (t_sprite*)malloc(sizeof(t_sprite) * \
		game->pedestal.quantity)))
		error_malloc(game);
	init_a_buff(&game->pedestal, game->pedestal.quantity);
	set_pedestal(game, &game->pedestal);
}
