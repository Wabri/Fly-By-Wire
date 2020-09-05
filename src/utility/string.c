#include <string.h>

int strExtrSeparator(char *dest, char *source, const char *separetor) {
  strcpy(dest, source);
  strtok(dest, separetor);
  return 0;
}

