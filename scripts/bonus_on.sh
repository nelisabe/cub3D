# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bonus_on.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 14:36:28 by nelisabe          #+#    #+#              #
#    Updated: 2020/10/24 16:09:17 by nelisabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

way="./game/core/cub3d.h"
if grep -q "BONUS 0" $way
    then sed -i 's/BONUS 0/BONUS 1/' $way
fi
echo -e "\033[31m\033[33mBONUS MODE\033[0m"