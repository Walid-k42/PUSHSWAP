/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wakhazza <wakhazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:59:08 by wakhazza          #+#    #+#             */
/*   Updated: 2026/01/26 20:12:56 by wakhazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_stack(t_node *a, t_config *config)
{
	ft_printf("\nStack A:\n");
	while (a)
	{
		ft_printf("%d\n", a->value);
		a = a->next;
	}
	ft_printf("\n");
	ft_printf("Strategy: ");
	if (config->strat == STRAT_SIMPLE)
		ft_printf("SIMPLE\n");
	else if (config->strat == STRAT_MEDIUM)
		ft_printf("MEDIUM\n");
	else if (config->strat == STRAT_COMPLEX)
		ft_printf("COMPLEX\n");
	else if (config->strat == STRAT_ADAPTIVE)
		ft_printf("ADAPTIVE\n");
	ft_printf("Bench mode: ");
	if (config->bench == 1)
		ft_printf("ON\n");
	if (config->bench == 0)
		ft_printf("OFF\n");
}

void	print_stacks(t_node *a, t_node *b)
{
	ft_printf("\nStack A:\n");
	while (a)
	{
		ft_printf("%d\n", a->value);
		a = a->next;
	}
	ft_printf("\nStack B:\n");
	while (b)
	{
		ft_printf("%d\n", b->value);
		b = b->next;
	}
}
void	chose_strat(t_config config, t_node **stack_a, t_node ** stack_b)
{
	if (config.strat == STRAT_ADAPTIVE)
		adaptive_strat(stack_a, stack_b);
	else if  (config.strat == STRAT_SIMPLE)
	{
		insertion_sort(stack_a, stack_b);
		ft_printf("simple");
	}
	else if  (config.strat == STRAT_MEDIUM)
	{
		chunk_sort(stack_a, stack_b);
		ft_printf("medium");
	}
}

void	adaptive_strat(t_node **stack_a, t_node ** stack_b)
{
	double	disorder;

	disorder = compute_disorder(*stack_a);
	if (disorder < 0.2)
	{
		insertion_sort(stack_a, stack_b);
		ft_printf("simple");
	}
	if (disorder >= 0.2 && disorder < 0.5)
	{
		chunk_sort(stack_a, stack_b);
		ft_printf("medium");
	}
	if (disorder >= 0.5)
	{
		chunk_sort(stack_a, stack_b);
		// complex.
		ft_printf("complex");
	}
		
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
		return (cleanup_error(&a));
	if (config.strat == STRAT_NONE)
		config.strat = STRAT_ADAPTIVE;
	if (!parse_numbers(strat, ac, av, &a))
		return (cleanup_error(&a));
	if (is_sorted(a))
		return (cleanup_error(&a)); // changer ca.
	ft_printf("%.2f\n", compute_disorder(a));
	// insertion_sort(&a, &b);
	find_index(&a);
	chose_strat(config, &a, &b);
	print_stacks(a, b);
	// chunk_sort(&a, &b);
	print_stacks(a, b);
	// free_stack(&a);
	return (0);
}
