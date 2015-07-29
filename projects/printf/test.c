#include <stdio.h>

int my_printf(const char *format, ...) __attribute__ ((format(printf, 1 ,2)));

int main(void)
{
  printf("\033[35;1mREAL PRINTF\033[0m\n");
  printf("%%c [%c] [%c] [%c] [%c] [%c]\n", 0x09, ' ', 42, 'a', 0x42);
  printf("%%i [%i] [%i] [%i] [%d] [%d] [%d]\n", 0, 1, 42, -42, 1337, -84);
  printf("%%o [%o] [%o] [%o] [%o] [%o] [%o]\n", 0, 1, 42, -42, 1337, -84);
  printf("%%p [%p] [%p] [%p] [%p]\n", NULL, &main, (void *)0xdeadbeef, (void *)((unsigned long)-1));
  printf("%%s [%s] [%s] [%s] [%s]\n", "", "toto42sh", "github.com", __FUNCTION__);
  printf("%%u [%u] [%u] [%u] [%u] [%u] [%u]\n", 0, 1, 42, -42, 1337, -84);
  printf("%%x [%x] [%x] [%x] [%x] [%x] [%x]\n", 0, 1, 42, -42, 1337, -84);
  my_printf("\033[36;1mMY_PRINTF\033[0m\n");
  my_printf("%%c [%c] [%c] [%c] [%c] [%c]\n", 0x09, ' ', 42, 'a', 0x42);
  my_printf("%%i [%i] [%i] [%i] [%d] [%d] [%d]\n", 0, 1, 42, -42, 1337, -84);
  my_printf("%%o [%o] [%o] [%o] [%o] [%o] [%o]\n", 0, 1, 42, -42, 1337, -84);
  my_printf("%%p [%p] [%p] [%p] [%p]\n", NULL, &main, (void *)0xdeadbeef, (void *)((unsigned long)-1));
  my_printf("%%s [%s] [%s] [%s] [%s]\n", "", "toto42sh", "github.com", __FUNCTION__);
  my_printf("%%u [%u] [%u] [%u] [%u] [%u] [%u]\n", 0, 1, 42, -42, 1337, -84);
  my_printf("%%x [%x] [%x] [%x] [%x] [%x] [%x]\n", 0, 1, 42, -42, 1337, -84);
}
