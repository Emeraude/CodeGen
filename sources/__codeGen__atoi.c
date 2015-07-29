/* function libc */
int	atoi(const char *nptr); /* stdlib.h */

/* function */
int	my_atoi(char *nptr)
{
  int	i;
  int	sign;
  int	nbr;

  if (nptr[0] == '-')
    {
      i = 0;
      sign = -1;
    }
  else
    {
      sign = 1;
      i = -1;
    }
  while (nptr[++i])
    nbr = nbr * 10 + nptr[i] - '0';
  return (nbr * sign);
}

/* function optimized register const ternary */
int		my_atoi(const char *const nptr)
{
  register int	i;
  int		nbr;

  i = (*nptr == '-' ? 0 : -1);
  while (nptr[++i])
    nbr = nbr * 10 + nptr[i] - '0';
  return (nbr * (*nptr == '-' ? -1 : 1));
}
