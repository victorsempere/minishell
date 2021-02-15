#include "minishell.h"

int				ft_job_is_stopped (t_job *j)
{
  t_process		*p;

  for (p = j->first_process; p; p = p->next)
    if (!p->completed && !p->stopped)
      return 0;
  return 1;
}