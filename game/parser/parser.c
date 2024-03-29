/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 13:57:04 by nelisabe          #+#    #+#             */
/*   Updated: 2020/10/24 15:20:15 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		init(char **line, t_pars *params)
{
	*line = NULL;
	params->r[0] = 0;
	params->r[1] = 0;
	params->no = NULL;
	params->so = NULL;
	params->we = NULL;
	params->ea = NULL;
	params->s = NULL;
	params->map = NULL;
	params->f[0] = 666;
	params->c[0] = 666;
}

static int		spaces_quant(char *line)
{
	int	quantity;

	quantity = 0;
	while (*line != ' ')
		line++;
	while (*line == ' ')
	{
		line++;
		quantity++;
	}
	return (quantity);
}

static int		get_pars(char *line, t_pars *params)
{
	const char	*vpars[8] = {"R ", "NO ", "SO ", \
				"WE ", "EA ", "S ", "F ", "C "};
	int			index;
	int			temp;

	index = -1;
	while (++index < 8)
	{
		if (index == 0 || index == 5 || index == 6 || index == 7)
			temp = 2;
		else
			temp = 3;
		if (ft_strnstr(line, vpars[index], temp))
			return (upd_pars(index, ft_strchr(line, ' ') + \
				spaces_quant(line), params));
	}
	if (*line == '\0')
		return (1);
	if (*line == '1' || *line == ' ')
		return (2);
	return (error_invalid_params(params));
}

static int		chk_filename(char *path)
{
	int	len;

	if ((len = ft_strlen(path)) < 5)
		return (1);
	if (ft_strncmp(&path[len - 4], ".cub", 5))
		return (1);
	return (0);
}

int				parser(char *path, t_pars *params)
{
	int		fd;
	int		temp;
	char	*line;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (!error_open_file());
	if (chk_filename(path))
		return (!error_wrong_filename());
	init(&line, params);
	while ((temp = get_next_line(fd, &line)))
	{
		if (temp == -1)
			return (!error_read_file_pars(fd, params));
		if (!(temp = get_pars(line, params)))
			return (!error_get_pars(&line, fd));
		if (temp == 2 && (error_in_params(params) || \
			!(temp = get_map(fd, line, params)) || temp == -1))
			return (!error_get_map(&line, fd, temp));
		free(line);
	}
	free(line);
	close(fd);
	if (error_invalid_file(params))
		return (1);
	return (0);
}
