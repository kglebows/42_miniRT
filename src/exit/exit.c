#include "minirt.h"

void	ft_exit(t_scene *scene)
{
	int		i;
	t_elem	*current;
	t_elem	*next;

	i = 0;
	current = scene->elements;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	scene->elements = NULL;
	if (scene->split != NULL)
		free_char_array(scene->split);
	exit(EXIT_FAILURE);
}
