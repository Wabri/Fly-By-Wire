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

  return 0;
}
