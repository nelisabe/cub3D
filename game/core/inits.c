/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 17:52:41 by nelisabe          #+#    #+#             */
/*   Updated: 2020/10/05 18:19:03 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//malloc protect

void	init_textures(t_core *game)
{
	game->frame.image = mlx_new_image(game->mlx, \
		game->params->r[0], game->params->r[1]);
	game->frame.img_addr = mlx_get_data_addr(game->frame.image, \
		&game->frame.bpp, &game->frame.size_line, \
		&game->frame.endian);
	load_image(game, &game->west, game->params->we);
	load_image(game, &game->north, game->params->no);
	load_image(game, &game->south, game->params->so);
	load_image(game, &game->east, game->params->ea);
	load_image(game, &game->sky, "./textures/sky3.xpm");
	load_image(game, &game->floor, "./textures/w.xpm");
	load_image(game, &game->face, "./textures/face.xpm");
}

void	init_map(t_core *game)
{
	game->map.x_pos = 0;
	game->map.y_pos = 0;
	game->map.y_scale = game->params->r[1] / 3 / game->map.map_lines;
	game->map.x_scale = game->params->r[0] / 3 / game->map.map_colunms;
	game->map.scale = game->map.y_scale < game->map.x_scale ? \
		game->map.y_scale : game->map.x_scale;
	game->map.sizeX = game->map.scale * game->map.map_colunms;
	game->map.sizeY = game->map.scale * game->map.map_lines;
}
	
void	init_game_settings(t_core *game)
{
	int	temp;

	game->centerX = game->params->r[0] / 2;
	game->centerY = game->params->r[1] / 2;
	game->player.x = 0;
	game->player.y = 0;
	game->map.block_size = 50;
	game->player.angle = 3 * M_PI / 2;
	game->player.speed = game->map.block_size * 0.06;
	game->player.fast_speed = game->player.speed * 2;
	game->player.button_angle_speed = 0.045;
	game->player.mouse_angle_speed = 0.005;
	game->player.radius = game->map.block_size * 0.2;
	game->player.fov = M_PI / 3;
	game->player.num_rays = game->params->r[0]; // 2;
	if (!(game->buffer = (t_ray_cast*)malloc(sizeof(t_ray_cast) * \
		game->player.num_rays)))
		return ;
	game->player.delta_angle = game->player.fov / game->player.num_rays;
	game->map.map_lines = -1;
	game->map.map_colunms = 0;
	while (game->params->map[++game->map.map_lines])
		if ((temp = ft_strlen(game->params->map[game->map.map_lines])) > \
			game->map.map_colunms)
			game->map.map_colunms = temp;
	game->frame.image = NULL;
}