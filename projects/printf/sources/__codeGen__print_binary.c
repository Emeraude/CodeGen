/* function */
void		print_binary(va_list *ap) /* stdarg.h */
{
  unsigned int	val;

  val = va_arg(ap, unsigned int);
  __codeGen__put_unsigned_nbr_base(val, "01");
}

/* function const */
void			print_binary(va_list *const ap) /* stdarg.h */
{
  unsigned int const	val = va_arg(ap, unsigned int);

  __codeGen__put_unsigned_nbr_base(val, "01");
}

/* function const optimized */
void			print_binary(va_list *const ap) /* stdarg.h */
{
  __codeGen__put_unsigned_nbr_base(va_arg(ap, unsigned int), "01");
}
