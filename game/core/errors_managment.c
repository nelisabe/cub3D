/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:59:36 by nelisabe          #+#    #+#             */
/*   Updated: 2020/10/18 20:37:58 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_a_buff(t_list **a_buff)
{
	t_list	*first;
	t_list	*temp;

	first = *a_buff;
	while ((*a_buff)->next != first)
	{
		temp = (*a_buff)->next;
		free(*a_buff);
		(*a_buff) = temp;
	}
	free(*a_buff);
}

void	free_object(t_core *game, t_object *object)
{
	int index;

	index = -1;
	if (object->tex)
	{
		while (object->tex[++index].img.image)
			if (object->tex[index].img.image)
				mlx_destroy_image(game->mlx, object->tex[index].img.image);
		free(object->tex);
	}
	if (object->pos)
	{
		if (object->pos->a_buff)
			free_a_buff(&object->pos->a_buff);
		free(object->pos);
	}
	index = -1;
	if (object->anim)
	{
		while (object->anim[++index].img.image)
			if (object->anim[index].img.image)
				mlx_destroy_image(game->mlx, object->anim[index].img.image);
		free(object->anim);
	}
}

void	free_sprites(t_core *game)
{
	free_object(game, &game->basic);
	free_object(game, &game->devil);
	free_object(game, &game->ghost);
	if (game->objects)
		free(game->objects);
}

void	free_images(t_core *game)
{
	if (game->west.img.image)
		mlx_destroy_image(game->mlx, game->west.img.image);	
	if (game->north.img.image)
		mlx_destroy_image(game->mlx, game->north.img.image);
	if (game->south.img.image)
		mlx_destroy_image(game->mlx, game->south.img.image);
	if (game->east.img.image)
		mlx_destroy_image(game->mlx, game->east.img.image);
	if (game->sky.img.image)
		mlx_destroy_image(game->mlx, game->sky.img.image);
	if (game->floor.img.image)
		mlx_destroy_image(game->mlx, game->floor.img.image);
}

int		free_structer(t_pars *params)
{
	int index;

	index = -1;
	free(params->no);
	free(params->so);
	free(params->we);
	free(params->ea);
	free(params->s);
	while (params->map[++index])
		free(params->map[index]);
	free(params->map);
	return (0);
}
