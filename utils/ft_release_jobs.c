#include "minishell.h"

void	ft_release_jobs(t_job *j)
{
	if (!j)
		return ;
	while ((j = ft_release_job(j))) ;
}