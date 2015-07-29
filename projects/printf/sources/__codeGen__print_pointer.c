/* function */
void		print_pointer(va_list *ap) /* stdarg.h */
{
  unsigned long	val;

  val = va_arg(ap, unsigned long);
  if (!val)
    {
      __codeGen__putstr("(nil)");
      return ;
    }
  __codeGen__putstr("0x");
  __codeGen__put_unsigned_nbr_base(val, "0123456789abcdef");
}

/* function */
void		print_pointer(va_list *ap) /* stdarg.h */
{
  unsigned long	val;

  val = va_arg(ap, unsigned long);
  if (!val)
    __codeGen__putstr("(nil)");
  else
    {
      __codeGen__putstr("0x");
      __codeGen__put_unsigned_nbr_base(val, "0123456789abcdef");
    }
}

/* function const optimized */
void			print_pointer(va_list *const ap) /* stdarg.h */
{
  unsigned long const	val = va_arg(ap, unsigned long);

  if (!val)
    {
      __codeGen__putstr("(nil)");
      return ;
    }
  __codeGen__putstr("0x");
  __codeGen__put_unsigned_nbr_base(val, "0123456789abcdef");
}

/* function const optimized */
void			print_pointer(va_list *const ap) /* stdarg.h */
{
  unsigned long const	val = va_arg(ap, unsigned long);

  if (!val)
    __codeGen__putstr("(nil)");
  else
    {
      __codeGen__putstr("0x");
      __codeGen__put_unsigned_nbr_base(val, "0123456789abcdef");
    }
}
