/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 23:07:31 by smickael          #+#    #+#             */
/*   Updated: 2018/03/30 23:07:31 by smickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isspace(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\n' || c == '\t'
			|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}