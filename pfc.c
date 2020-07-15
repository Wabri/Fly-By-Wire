
/*
 *
 * Hello world!
 *
 */

#include <stdio.h>

int main(void) {

  // declarations
  int iValorized;
  iValorized = 5;
  const float fPi = 3.14159265;

  printf("%f \n", fPi);

  printf("n %d\n", iValorized);
  printf("n++ %d\n", iValorized++);
  printf("++n %d\n", ++iValorized);
  printf("n-- %d\n", iValorized--);
  printf("--n %d\n", --iValorized);

  printf("+n %d\n", +iValorized);
  printf("-n %d\n", -iValorized);

  int iValorized2 = 14 % 3;

  printf("n2 = %d\n", iValorized2);
  printf("n+n2 %d\n", iValorized + iValorized2);
  printf("n-n2 %d\n", iValorized - iValorized2);
  printf("n/n2 %d\n", iValorized / iValorized2);

  iValorized += iValorized2;
  printf("n+=n2 %d\n", iValorized);

  iValorized -= iValorized2;
  printf("n-=n2 %d\n", iValorized);

  iValorized *= iValorized2;
  printf("n*=n2 %d\n", iValorized);

  iValorized /= iValorized2;
  printf("n/=n2 %d\n", iValorized);

  return 0;
}
