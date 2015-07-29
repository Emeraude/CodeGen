/* function */
void	print_modulo(va_list *ap)
{
  (void)ap;
  __codeGen__putchar('%');
}

/* function attribute */
void	print_modulo(va_list *ap __attribute__ ((unused)))
{
  __codeGen__putchar('%');
}

/* function const attribute optimized */
void	print_modulo(va_list *const ap __attribute__ ((unused)))
{
  __codeGen__putchar('%');
}

/* function const */
void	print_modulo(va_list *const ap)
{
  (void)ap;
  __codeGen__putchar('%');
}
