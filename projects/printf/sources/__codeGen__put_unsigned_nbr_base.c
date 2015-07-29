/* function rec */
void	my_put_unsigned_nbr_base(unsigned long nbr, char *base)
{
  if (nbr > __codeGen__strlen(base) - 1)
    my_put_unsigned_nbr_base(nbr / __codeGen__strlen(base), base);
  __codeGen__putchar(base[nbr % __codeGen__strlen(base)]);
}

/* function rec const optimized */
void	my_put_unsigned_nbr_base(unsigned long const nbr, char const *const base)
{
  if (nbr > __codeGen__strlen(base) - 1)
    my_put_unsigned_nbr_base(nbr / __codeGen__strlen(base), base);
  __codeGen__putchar(base[nbr % __codeGen__strlen(base)]);
}
