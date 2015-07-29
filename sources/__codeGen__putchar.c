/* function libc */
int	putchar(int c); /* stdio.h */

/* function */
int	my_putchar(int c) /* unistd.h */
{
  if (write(1, &c, 1) != 1)
    return (-1);
  return (c);
}

/* function ternary const */
int	my_putchar(const int c) /* unistd.h */
{
  return (write(1, &c, 1) == 1 ? c : -1);
}
