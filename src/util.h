#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define PANIC(fmt, ...)                                        \
    do                                                         \
    {                                                          \
        printf("ERROR: %d: " fmt "\n", __LINE__, __VA_ARGS__); \
        exit(1);                                               \
    } while (0)

#ifdef __cplusplus
extern "C" {
#endif

char *read_file_as_str(const char *fp);

#ifdef __cplusplus
}
#endif

#endif // UTIL_H

#ifdef UTIL_IMPLEMENTATION

char *read_file_as_str(const char *fp)
{
    size_t nch = 0;
    FILE *f = fopen(fp, "r");
    if (f == 0)
        PANIC("ERROR: opening file %s\n", fp);
    int c;
    size_t size = 1024;
    char *buf = (char *)malloc(size);
    if (buf == 0)
        PANIC("ERROR: memory allocation failed%s\n", "");

    while ((c = getc(f)) != EOF)
    {
        if (nch >= size - 1)
        {
            size *= 2;
            buf = (char *)realloc(buf, size);
            if (buf == 0)
                PANIC("ERROR: memory allocation failed%s\n", "");
        }
        buf[nch++] = c;
    }

    buf[nch++] = 0;
    fclose(f);
    return buf;
}

#endif // UTIL_IMPLEMENTATION
