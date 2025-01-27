/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:57:31 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/27 10:58:32 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H

# include <stdbool.h>
# include <stdlib.h>
# include <time.h>

int		randint(int min, int max);
bool	randbool(int prob);

#endif // RANDOM_H
