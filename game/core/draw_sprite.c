/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:52:06 by nelisabe          #+#    #+#             */
/*   Updated: 2020/10/23 19:32:34 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		needed_side(t_sprite *sprite)
{
	int		num;
	double	angle;

	num = 0;
	angle = 360;
	if (sprite->volume == 1)
	{
		if (sprite->theta < 22.5 || sprite->theta > 337.5)
			num = 6;
		if (sprite->theta < 67.5 && sprite->theta > 22.5)
			num = 7;
		if (sprite->theta < 112.5 && sprite->theta > 67.5)
			num = 0;
		if (sprite->theta < 157.5 && sprite->theta > 112.5)
			num = 1;
		if (sprite->theta < 202.5 && sprite->theta > 157.5)
			num = 2;
		if (sprite->theta < 247.5 && sprite->theta > 202.5)
			num = 3;
		if (sprite->theta < 292.5 && sprite->theta > 247.5)
			num = 4;
		if (sprite->theta < 337.5 && sprite->theta > 292.5)
			num = 5;
	}
	return (num);
}

static void		type_of_sprite(t_core *game, t_sprite *sprite, \
	t_tex **texture, int num)
{
	if (sprite->type != '2')
		if ((sprite->depth < game->map.block_size * 5 || \
			sprite->type == 'b' || sprite->type == 'f' || \
			sprite->type == 's') && sprite->a_buff)
		{
			*texture = sprite->a_buff->content;
			if (sprite->a_tmp++ == sprite->a_speed)
			{
				sprite->a_buff = sprite->a_buff->next;
				sprite->a_tmp = 0;
			}
		}
		else
		{
			if (sprite->type == 'd')
				*texture = &game->devil.tex[num];
			if (sprite->type == 'g')
				*texture = &game->ghost.tex[num];
			if (sprite->type == 'p')
				*texture = &game->pedestal.tex[num];
		}
	else
		*texture = &game->basic.tex[num];
}

static void		calc_properties(t_core *game, t_sprite *sprite, t_tex **texture)
{
	if (sprite->theta < 0)
		sprite->theta += 2 * M_PI;
	sprite->theta = 360 - sprite->theta * 180 / M_PI;
	type_of_sprite(game, sprite, texture, needed_side(sprite));
	sprite->heigth = (int)game->params->r[1] / (sprite->depth / \
		game->map.block_size) * sprite->scale_y;
	sprite->width = (int)game->params->r[1] / (sprite->depth /
		game->map.block_size) * sprite->scale_x;
	(*texture)->step = (*texture)->height / sprite->heigth;
	(*texture)->step_x = (*texture)->width / sprite->width;
	sprite->cw = sprite->width >= game->params->r[0] ? \
		game->params->r[0] - 1 : (int)sprite->width;
	sprite->ch = (int)sprite->heigth;
	(*texture)->x_screen = sprite->ray - sprite->width / 2;
	(*texture)->x_texture = 0;
	if ((*texture)->x_screen < 0)
	{
		(*texture)->x_texture += -1 * (*texture)->x_screen * (*texture)->step_x;
		(*texture)->x_screen = 0;
	}
}

void			draw_sprite(t_core *game, t_sprite *sprite)
{
	t_tex	*texture;
	double	ccw;
	double	cch;

	calc_properties(game, sprite, &texture);
	ccw = sprite->cw;
	while (ccw-- && texture->x_texture < texture->width \
		&& texture->x_screen < game->params->r[0])
	{
		cch = sprite->ch;
		texture->y_screen = game->params->r[1] / 2 - sprite->ch * sprite->z;
		texture->y_texture = (texture->y_screen - game->params->r[1] / \
			2 + sprite->heigth * sprite->z) * texture->step;
		while (cch--)
		{
			if (texture->y_screen >= 0 && texture->y_screen < \
				game->params->r[1])
				set_pixel(game, texture, sprite->depth);
			texture->y_screen++;
			texture->y_texture += texture->step;
		}
		texture->x_screen++;
		texture->x_texture += texture->step_x;
	}
}
