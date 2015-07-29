/* function rec */
void	my_putnbr_base(long nbr, char *base)
{
  if (nbr < 0)
    {
      nbr = -nbr;
      __codeGen__putchar('-');
    }
  if (nbr > (int)__codeGen__strlen(base) - 1)
    my_putnbr_base(nbr / __codeGen__strlen(base), base);
  __codeGen__putchar(base[nbr % __codeGen__strlen(base)]);
}

/* function rec const */
void	my_putnbr_base(long const nbr, char const *const base)
{
  if (nbr < 0)
    {
      __codeGen__putchar('-');
      my_putnbr_base(-nbr, base);
      return ;
    }
  if (nbr > (int)__codeGen__strlen(base) - 1)
    my_putnbr_base(nbr / __codeGen__strlen(base), base);
  __codeGen__putchar(base[nbr % __codeGen__strlen(base)]);
}
