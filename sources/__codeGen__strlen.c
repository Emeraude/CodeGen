/* function libc */
size_t	strlen(const char *s); /* stddef.h string.h */

/* function */
size_t		my_strlen(char *s) /* stddef.h */
{
  size_t	i;

  i = 0;
  while (s[i])
    ++i;
  return (i);
}

/* function rec tail-rec ternary */
size_t	my_strlen(char *s) /* stddef.h */
{
  return (*s ? 1 + my_strlen(s + 1) : 0);
}

/* function for */
size_t		my_strlen(char *s) /* stddef.h */
{
  size_t	i;

  for (i = 0; s[i]; ++i);
  return (i);
}

/* function optimized register const */
size_t			my_strlen(const char *const s) /* stddef.h */
{
  register size_t	i;

  i = 0;
  while (s[i])
    ++i;
  return (i);
}
