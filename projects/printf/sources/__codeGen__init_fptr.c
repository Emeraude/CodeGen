/* function optimized */
void	init_fptr(void)
{
  g_fptr['b'] = &__codeGen__print_binary;
  g_fptr['c'] = &__codeGen__print_char;
  g_fptr['d'] = &__codeGen__print_int;
  g_fptr['i'] = &__codeGen__print_int;
  g_fptr['o'] = &__codeGen__print_octal;
  g_fptr['p'] = &__codeGen__print_pointer;
  g_fptr['s'] = &__codeGen__print_string;
  g_fptr['u'] = &__codeGen__print_unsigned;
  g_fptr['x'] = &__codeGen__print_hexa;
  g_fptr['%'] = &__codeGen__print_modulo;
}

/* function */
void	init_fptr(void)
{
  if (!g_fptr['b'])
    {
      g_fptr['b'] = &__codeGen__print_binary;
      g_fptr['c'] = &__codeGen__print_char;
      g_fptr['d'] = &__codeGen__print_int;
      g_fptr['i'] = &__codeGen__print_int;
      g_fptr['o'] = &__codeGen__print_octal;
      g_fptr['p'] = &__codeGen__print_pointer;
      g_fptr['s'] = &__codeGen__print_string;
      g_fptr['u'] = &__codeGen__print_unsigned;
      g_fptr['x'] = &__codeGen__print_hexa;
      g_fptr['%'] = &__codeGen__print_modulo;
    }
}
