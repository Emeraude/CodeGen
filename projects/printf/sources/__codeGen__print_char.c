/* function */
void	print_char(va_list *ap) /* stdarg.h */
{
  char	val;

  val = va_arg(ap, int);
  __codeGen__putchar(val);
}

/* function const */
void		print_char(va_list *const ap) /* stdarg.h */
{
  char const	val = va_arg(ap, int);

  __codeGen__putchar(val);
}

/* function const optimized */
void			print_char(va_list *const ap) /* stdarg.h */
{
  __codeGen__putchar(va_arg(ap, int));
}
