#include "mini_shell.h"

void	ft_free_chr(char **super)
{
	int	i;

	i = 0;
	while (super[i])
	{
		free(super[i]);
		i++;
	}
	free(super);
	super = NULL;
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	ft_free_env(t_envi *head)
{
   t_envi   *current;
   t_envi   *next;

   current = head;
   next = NULL;
   while (current)
   {
      next = current->next;
      free(current->str);
      free(current);
      current = next;
   }
   head = NULL;
}