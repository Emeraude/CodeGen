/* function */
int		my_printf(const char *format, ...) /* stdarg.h */
{
  va_list	ap;
  int		i;

  if (!g_fptr['b'])
    init_fptr();
  va_start(ap, format);
  i = -1;
  while (format[++i])
    {
      if (format[i] == '%'
	  && format[i + 1])
	{
	  if (g_fptr[(int)format[i + 1]])
	    g_fptr[(int)format[++i]](&ap);
	  else
	    __codeGen__putchar('%');
	}
      else
	__codeGen__putchar(format[i]);
    }
  va_end(ap);
  return (0);
}
