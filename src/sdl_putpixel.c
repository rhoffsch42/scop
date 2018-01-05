/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_putpixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:09:01 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:09:05 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	sdl_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		*p = pixel;
	else if (bpp == 2)
		*(Uint16 *)p = pixel;
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
	}
	else if (bpp == 4)
		*(Uint32*)p = pixel;
	else
		ft_errexit("Bad BytesPerPixel value", RED, SDL_BAD_BPP);
}
