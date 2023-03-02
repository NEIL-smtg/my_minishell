/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:26:46 by suchua            #+#    #+#             */
/*   Updated: 2022/11/07 19:22:07 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst -> next;
	}
	return (size);
}

// int	main(void)
// {
// 	t_list *l =  NULL;

// 	printf("l %d\n", ft_lstsize(l));
// 	ft_lstadd_front(&l, ft_lstnew((void *)2));
// 	printf("l %d\n", ft_lstsize(l));
// 	return (0);
// }