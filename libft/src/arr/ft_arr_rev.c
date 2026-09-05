
#include "libft_arr.h"

static void ft_switch_ptr(void **a, void **b)
{
	void *c;

	c = *a;
	*a = *b;
	*b = c;
}

// reverse the first n elemnts of the array
void	ft_arr_rev_n(t_arr_el *arr, size_t n)
{
	size_t i = 0;
	while (i < n / 2)
	{
		ft_switch_ptr(&arr[i], &arr[n - i - 1]);
		i++;
	}
}

void	ft_arr_rev(t_arr arr)
{
	size_t	len;

	len = ft_arr_len(arr);
	ft_arr_rev_n(arr, len);
}
