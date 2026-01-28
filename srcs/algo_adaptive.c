/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wakhazza <wakhazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:27:52 by wakhazza          #+#    #+#             */
/*   Updated: 2026/01/28 11:30:49 by wakhazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	chose_strat(t_config config, t_node **stack_a, t_node **stack_b)
{
	if (config.strat == STRAT_ADAPTIVE)
		adaptive_strat(stack_a, stack_b, &config);
	else if (config.strat == STRAT_SIMPLE)
		insertion_sort(stack_a, stack_b, &config);
	else if (config.strat == STRAT_MEDIUM)
		chunk_sort(stack_a, stack_b, &config);
	else if (config.strat == STRAT_COMPLEX)
	{
		compress_stack_to_index(*stack_a);
		radix_sort(stack_a, stack_b, &config);
	}
}

void	adaptive_strat(t_node **stack_a, t_node **stack_b, t_config *config)
{
	double	disorder;

	disorder = compute_disorder(*stack_a);
	if (disorder < 0.2)
		insertion_sort(stack_a, stack_b, config);
	if (disorder >= 0.2 && disorder < 0.5)
		chunk_sort(stack_a, stack_b, config);
	if (disorder >= 0.5)
	{
		compress_stack_to_index(*stack_a);
		radix_sort(stack_a, stack_b, config);
	}
}
