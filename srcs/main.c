/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wakhazza <wakhazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:59:08 by wakhazza          #+#    #+#             */
/*   Updated: 2026/01/28 11:31:11 by wakhazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_bench(t_config *config)
{
	if (!config->bench)
		return ;
	ft_putnbr_fd(config->total, 2);
	ft_putnbr_fd(config->counts[COUNT_PA], 2);
	ft_putnbr_fd(config->counts[COUNT_PB], 2);
	ft_putnbr_fd(config->counts[COUNT_SA], 2);
	ft_putnbr_fd(config->counts[COUNT_SB], 2);
	ft_putnbr_fd(config->counts[COUNT_SS], 2);
	ft_putnbr_fd(config->counts[COUNT_RA], 2);
	ft_putnbr_fd(config->counts[COUNT_RB], 2);
	ft_putnbr_fd(config->counts[COUNT_RR], 2);
	ft_putnbr_fd(config->counts[COUNT_RRA], 2);
	ft_putnbr_fd(config->counts[COUNT_RRB], 2);
	ft_putnbr_fd(config->counts[COUNT_RRR], 2);
}

int	main(int ac, char **av)
{
	t_node		*a;
	t_node		*b;
	t_config	config;
	int			strat;

	a = NULL;
	b = NULL;
	if (ac < 2)
		return (0);
	config.strat = STRAT_NONE;
	config.bench = 0;
	strat = parse_flags(ac, av, &config);
	if (strat < 0)
		return (cleanup_error(&a, 0));
	if (config.strat == STRAT_NONE)
		config.strat = STRAT_ADAPTIVE;
	if (!parse_numbers(strat, ac, av, &a))
		return (cleanup_error(&a, 0));
	if (is_sorted(a))
		return (cleanup_error(&a, 1));
	find_index(&a);
	chose_strat(config, &a, &b);
	print_bench(&config);
	free_stack(&a);
	return (0);
}
