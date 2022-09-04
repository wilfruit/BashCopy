#include "mini_shell.h"

static int	ft_lstlen(t_envi *env)
{
	int	size;
	t_envi	*temp;

	temp = env;

	size = 0;
	if (temp)
		size++;
	else
		return (0);
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	free(temp);
	return (size);
}

static char	**transform_env(t_envi *env)
{
	char	**ret;
	t_envi	*temp;
	int	i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (ft_lstlen(env) + 1));
	if (!ret)
		return NULL;
	temp = env;
	while (temp /* && temp->next != NULL */)
	{
		ret[i] = (char *)malloc(sizeof(char) * ft_strlen(temp->str));
		if (!ret)
			perror("malloc : ");
		ret[i] = ft_strdup(temp->str);
		temp = temp->next;
		i++;
	}
	ret[i] = "\0";
	free(temp);
	return (ret);
}

static void alpha_sort(char **env)
{
	char *temp;
	int i;
	int	j;

	i = 0;
	temp = NULL;
	while (ft_strncmp(env[i], "\0", ft_strlen(env[i])) != 0)
	{
		j = 0;
    	while(ft_strncmp(env[j], "\0", ft_strlen(env[j])))
		{
      		if(ft_strncmp(env[j], env[j+1], ft_strlen(env[j])) > 0 \
			&& ft_strncmp(env[j + 1], "\0", ft_strlen(env[j + 1])))
	  		{
				temp = ft_strdup(env[j]);
				env[j] = ft_strdup(env[j + 1]);
				env[j + 1] = ft_strdup(temp);
    		}
			j++;
		}
		i++;
	}
}

static void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "\0", ft_strlen(env[i])))
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	my_exprint(t_envi *env)
{
	char	**unsorted_env;
	char	**sorted_env;

	unsorted_env = (char **)malloc(sizeof(char *) * ft_lstlen(env) + 1);
	if (!unsorted_env)
		perror ("Malloc :");
	unsorted_env = transform_env(env);
	alpha_sort(unsorted_env);
	ft_print_env(unsorted_env);
//	ft_print_env(unsorted_env);
//	ft_free_chr(unsorted_env);
//	ft_free_chr(sorted_env);
}