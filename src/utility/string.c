#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strExtrSeparator(char *dest, char *source, const char *separetor) {
    strcpy(dest, source);
    strtok(dest, separetor);
    return 0;
}

void strExtrInterval(char *dest, char *source, int start, int end) {
    // printf("%d,%d\n", start, end);
    if (start <= end) {
        for (int i = start, j = 0; i <= end; i++, j++) {
            if (source[i] != '\0') {
                dest[j] = source[i];
            }
        }
    } else {
        dest[0] = '\0';
    }
}
