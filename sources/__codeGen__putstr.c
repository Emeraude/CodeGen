/* function optimized const */
ssize_t	my_putstr(const char *const s) /* unistd.h */
{
  return (write(1, s, __codeGen__strlen(s)));
}

/* function */
ssize_t	my_putstr(char *s)
{
  int	i;

  i = -1;
  while (s[++i])
    if (__codeGen__putchar(s[i]) == -1)
      return -1;
  return i;
}
