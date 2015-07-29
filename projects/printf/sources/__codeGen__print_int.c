/* function */
void	print_int(va_list *ap) /* stdarg.h */
{
  int	val;

  val = va_arg(ap, int);
  __codeGen__putnbr_base(val, "0123456789");
}

/* function const */
void		print_int(va_list *const ap) /* stdarg.h */
{
  int const	val = va_arg(ap, int);

  __codeGen__putnbr_base(val, "0123456789");
}

/* function const optimized */
void			print_int(va_list *const ap) /* stdarg.h */
{
  __codeGen__putnbr_base(va_arg(ap, int), "0123456789");
}
