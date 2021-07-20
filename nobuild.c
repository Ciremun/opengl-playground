#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SOURCES "src/main.cpp"
#define OUTPUT "opengl-playground"

#ifdef _WIN32
#define LIBS "-lglew32", "-lglfw3", "-lopengl32"
#define FILENAME OUTPUT ".exe"
#define RUN ".\\" FILENAME
#else
#define LIBS "-lGLEW", "-lglfw", "-lGL"
#define RUN "./" OUTPUT
#define FILENAME OUTPUT
#endif

#define CXXFLAGS "-Wall", "-Wextra", "-pedantic", "-std=c++17", "-ggdb", "-O0"

char *read_file_as_str(const char *fp, size_t *nch)
{
    size_t nch_;
    if (nch == 0)
    {
        nch_ = 0;
        nch = &nch_;
    }
    FILE *f = fopen(fp, "r");
    if (f == 0)
        PANIC("ERROR:%d: opening file %s\n", __LINE__, fp);
    int c;
    size_t size = 1024;
    char *buf = malloc(size);
    if (buf == 0)
        PANIC("ERROR:%d: memory allocation failed\n", __LINE__);

    while ((c = getc(f)) != EOF)
    {
        if (*nch >= size - 1)
        {
            size *= 2;
            buf = realloc(buf, size);
            if (buf == 0)
                PANIC("ERROR:%d: memory allocation failed\n", __LINE__);
        }
        buf[(*nch)++] = c;
    }

    buf[(*nch)++] = 0;
    fclose(f);
    return buf;
}

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);

    char *cxx = getenv("cxx");
    if (cxx == 0)
        cxx = "g++";

    if (PATH_EXISTS(FILENAME) && (is_path1_modified_after_path2("src/shaders/vertex.glsl", FILENAME) ||
        is_path1_modified_after_path2("src/shaders/fragment.glsl", FILENAME)))
    {
        char *vertex_shader_source = read_file_as_str("src/shaders/vertex.glsl", 0);
        char *fragment_shader_source = read_file_as_str("src/shaders/fragment.glsl", 0);

        FILE *f = fopen("src/shaders.h", "wb");
        if (f == 0)
            PANIC("ERROR:%d: opening file %s\n", __LINE__, "src/shaders.h");
        fprintf(f, "constexpr const char* VERTEX_SHADER_SOURCE = R\"(%s)\";\n", vertex_shader_source);
        fprintf(f, "constexpr const char* FRAGMENT_SHADER_SOURCE = R\"(%s)\";", fragment_shader_source);
        fclose(f);

        free(vertex_shader_source);
        free(fragment_shader_source);
    }

    CMD(cxx, SOURCES, CXXFLAGS, "-oopengl-playground", LIBS);

    if (argc > 1)
    {
        if (strcmp(argv[1], "run") == 0)
            CMD(RUN);
    }
}
