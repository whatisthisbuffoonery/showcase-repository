/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:21:33 by achew             #+#    #+#             */
/*   Updated: 2025/12/15 14:23:13 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	minus_count;

	i = 0;
	result = 0;
	minus_count = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus_count++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (minus_count % 2 != 0)
		result *= -1;
	return (result);
}

//int	main(int argc, char *argv[])
//{
//	int	i;
//	
//	i = 0;
//	while (i < argc)
//	{
//		printf("Argument %d: %s\n", i, argv[i]);
//		i++;
//	}
//	printf("There are %d arguments\n", argc);
//	printf("The return value of ft_atoi is %d\n", ft_atoi(argv[1]));
//	printf("The return value of atoi is %d", atoi(argv[1]));
//	return (0);
//}
