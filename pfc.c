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

  printf("n2 %d\n", iValorized2);
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

  printf("n==n2 %d \n", iValorized == iValorized2);

  printf("n!=n2 %d \n", iValorized != iValorized2);

  printf("n<n2 %d \n", iValorized < iValorized2);

  printf("n>n2 %d \n", iValorized > iValorized2);

  printf("n<=n2 %d \n", iValorized <= iValorized2);

  printf("n>=n2 %d \n", iValorized >= iValorized2);

  int bVal = 0;
  int bVal2 = 1;

  printf("b %d \n", bVal);

  printf("!b %d \n", !bVal);

  printf("b && b2 %d \n", bVal && bVal2);

  printf("b || b2 %d \n", bVal || bVal2);

  int iValorized3 = (bVal++ && --bVal2) ? iValorized : iValorized2;

  printf("n3 %d \n", iValorized3);

  /*
   * Ci sono altri operatori logici binari:
   *   * op1 & op2 AND bit a bit
   *   * op1 | op2 OR bit a bit
   *   * op1 ^ op2 XOR bit a bit
   *   * op1 << op2 spostamento a sinistra di op2 bit
   *   * op1 >> op2 spostamento a destra di op2 bit
   *   * ~op1 completamento a 1
   *   * op1 &= op2
   *   * op1 |= op2
   *   * op1 ^= op2
   *   * op1 <<= op2
   *   * op1 >>= op2
   *   * op1 ~= op2
   */

  printf("5/4 = %d \n", 5 / 4);

  printf("5.0/4.0 = %f \n", 5.0 / 4.0);

  printf("(cast)(5/4) = %f \n", (double)(5 / 4));

  printf("(cast)5/4 = %f \n", (double)5 / 4);

  iValorized = iValorized2, iValorized2 = ++iValorized3;

  printf("n, n2 %d, %d \n", iValorized, iValorized2);

  int count = 0;

  printf("start \n");

label:

  count++;

  printf("counter at %d \n", count);

  switch (count) {
  case 1:
    goto label;
  case 2:
    goto label;
  case 3:
    goto stop;
  case 4:
    printf("Something happened with counter at %d \n", count);
    break;
  case 5:
    printf("Counter at %d \n", count);
    break;
  }

stop:
  printf("cycle stops at %d \n", count);

  if (count < 5) {
    goto label;
  }

  while (count <= 8) {
    count++;
    if (count == 7) {
      printf("It stops with 7 \n");
      break;
    } else {
      printf("It continue != 7 \n");
      continue;
    }
    goto label;
  }

  return 0;
}
