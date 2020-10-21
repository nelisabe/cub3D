/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 19:05:07 by nelisabe          #+#    #+#             */
/*   Updated: 2020/10/21 23:24:17 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BONUS 0

# include "../utils/libft/libft.h"
# include "../utils/get_next_line/get_next_line.h"
# include "../../minilibx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef	struct	s_pars
{
	int		r[2];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		f[3];
	int		c[3];
	char	**map;
}				t_pars;

typedef	struct	s_img
{
	void	*image;
	char	*img_addr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef	struct	s_buttons
{
	int a;
	int s;
	int d;
	int w;
	int left;
	int right;
	int	shift;
}				t_buttons;

typedef	struct	s_flr_ceil
{
	double	floor_x;
	double	floor_y;
	double	dist_to_wall;
	double	screen_dist;
	int		lineheight;
	double	weight;
	double	screen_floor_x;
	double	screen_floor_y;
}				t_flr_ceil;

typedef	struct	s_tex
{
	t_img	img;
	int		width;
	int		height;
	double	offset;
	int		proj_copy;
	double	step;
	double	step_x;
	double	x_screen;
	double	y_screen;
	double	x_texture;
	double	y_texture;
}				t_tex;

typedef	struct	s_ray_cast
{
	char	type;
	double	current_angle;
	int		num_rays;
	double	wall_height;
	double	x;
	double	y;
	double	xh;
	double	yv;
	double	dx;
	double	dy;
	double	xm;
	double	ym;
	double	depth;
	double	depth_v;
	double	depth_h;
}				t_ray_cast;

typedef	struct	s_map
{
	int	x_scale;
	int	y_scale;
	int	scale;
	int	x_pos;
	int	y_pos;
	int	map_lines;
	int	map_colunms;
	int	block_size;
	int	walls_color;
	int	space_color;
	int	player_color;
}				t_map;

typedef	struct	s_player
{
	double	angle;
	double	speed;
	double	cur_speed;
	double	fast_speed;
	double	button_angle_speed;
	double	mouse_angle_speed;
	double	radius;
	double	fov;
	int		num_rays;
	double	delta_angle;
	double	x;
	double	y;
}				t_player;

typedef	struct	s_sprite
{
	char	type;
	double	x;
	double	y;
	double	z;
	double	depth;
	double	heigth;
	double	width;
	double	ch;
	double	cw;
	double	scale_x;
	double	scale_y;
	double	angle;
	double	dx;
	double	dy;
	double	gamma;
	double	theta;
	double	drays;
	double	ray;
	int		volume;
	int		a_tmp;
	int		a_speed;
	t_list	*a_buff;
}				t_sprite;

typedef	struct	s_object
{
	t_tex		*tex;
	t_sprite	*pos;
	t_tex		*anim;
	int			quantity;
}				t_object;

typedef	struct	s_core
{
	t_pars		*params;
	int			save;
	void		*mlx;
	void		*window;
	t_ray_cast	*buffer;
	int			center_x;
	int			center_y;
	int			color;
	double		shadow;
	t_buttons	button;
	t_map		map;
	t_player	player;
	t_img		frame;
	t_tex		west;
	t_tex		north;
	t_tex		south;
	t_tex		east;
	t_tex		wall;
	t_tex		wall_dirty;
	t_tex		sky;
	t_tex		floor;
	t_tex		face;
	t_object	basic;
	t_object	devil;
	t_object	ghost;
	t_object	fire;
	t_object	barrel;
	t_object	pedestal;
	t_object	skull;
	t_object	**objects;
}				t_core;

int				cub3d(char *path, char *flag);
void			load_image(t_core *game, t_tex *texture, char *path);
void			init_pointers(t_core *game);
void			init_window(t_core *game);
void			init_textures(t_core *game);
void			init_sprites(t_core *game);
void			init_load_tex_images(t_core *game, t_object *object, \
	char *path, int quantity);
void			init_load_anim_images(t_core *game, t_object *object, \
	char *path, int quantity);
void			create_anim_buff(t_core *game, t_tex *anim, t_list **a_buff, \
	int quant);
void			set_spr(t_sprite *sprite, double x, double y, double z);
void			place_on_map(t_core *game, double x, double y, char object);
void			init_basic(t_core *game, char *path);
void			init_game_settings(t_core *game);
void			init_map(t_core *game);
void			init_ghost(t_core *game, char *path);
void			init_devil(t_core *game, char *path);
void			init_a_buff(t_object *sprite, int quant);
void			init_fire(t_core *game, char *path);
void			init_barrel(t_core *game, char *path);
void			init_pedestal(t_core *game, char *path);
void			init_skull(t_core *game, char *path);
int				free_structer(t_pars *params);
void			free_images(t_core *game);
void			free_sprites(t_core *game);
int				parser(char *path, t_pars *params);
int				render(t_core *game);
void			pixel_put(t_img image, int x, int y, int color);
int				handler(t_core *game);
void			set_pixel(t_core *game, t_tex *texture, double depth);
void			free_lst(t_list **lst);
int				map(t_core *game);
int				player(t_core *game);
int				ray_casting(t_core *game);
int				object_check(t_core *game, double x, double y, char object);
int				check_wall_type(t_core *game, double x, double y, char object);
void			make_frame(t_core *game);
void			texture_wall(t_core *game, t_ray_cast *ray);
int				make_darker(double depth, int r, int g, int b);
void			set_back_colors(t_core *game);
void			set_sky(t_core *game, t_ray_cast *ray);
void			set_floor_ceiling(t_core *game, t_ray_cast *ray);
void			sprite(t_core *game, t_ray_cast *ray);
int				sort_walls(t_core *game, t_ray_cast **buffer, t_list **walls);
void			calc_sprites_params(t_core *game, t_object *object);
void			find_visible_sprites(t_core *game, t_object *object, \
	t_list **sprites);
int				needed_side(t_sprite *sprite);
void			type_of_sprite(t_core *game, t_sprite *sprite, \
	t_tex **texture, int num);
void			draw_sprite(t_core *game, t_sprite *sprite);
void			error_creation_window(t_core *game);
void			error_mlx_init(t_core *game);
void			error_malloc_buffer(t_core *game);
void			error_creation_frame_image(t_core *game);
void			error_open_xpm_file(t_core *game, char *path);
void			error_malloc(t_core *game);
void			error_newlst(t_core *game, t_list **list);
void			error_newlsts(t_core *game, t_list **list_1, t_list **list_2);
void			error_creating_file(t_core *game, unsigned char **memory);
int				exit_cub3d(t_core *game);

#endif
