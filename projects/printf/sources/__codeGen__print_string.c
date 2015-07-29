/* function */
void	print_string(va_list *ap) /* stdarg.h */
{
  char	*val;

  val = va_arg(ap, char *);
  __codeGen__putstr(val);
}

/* function const */
void			print_string(va_list *const ap) /* stdarg.h */
{
  char *const const	val = va_arg(ap, char const *);

  __codeGen__putstr(val);
}

/* function const optimized */
void			print_string(va_list *const ap) /* stdarg.h */
{
  __codeGen__putstr(va_arg(ap, char const *));
}
