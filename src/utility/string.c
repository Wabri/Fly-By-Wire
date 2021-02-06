#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strExtrSeparator(char *dest, char *source, const char *separator)
{
    strcpy(dest, source);
    strtok(dest, separator);
    return 0;
}

unsigned int strSeparatorIndex(char *source, const char separator)
{
    for (int i = 0; i < strlen(source); i += 1)
    {
        if (source[i] == separator)
        {
            return i;
        }
    }
    return strlen(source);
}

void strExtrInterval(char *dest, char *source, int start, int end)
{
    if (start <= end)
    {
        for (int i = start, j = 0; i <= end; i++, j++)
        {
            if (source[i] != '\0')
            {
                dest[j] = source[i];
            }
        }
    }
    else
    {
        dest[0] = '\0';
    }
}
