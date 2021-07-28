#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define UTIL_IMPLEMENTATION
#include "src/util.h"

#define SOURCES "src/main.cpp"
#define OUTPUT "opengl-playground"

#ifdef _WIN32
#define LIBS "-lglew32", "-lglfw3", "-lopengl32"
#define FILENAME OUTPUT ".exe"
#define RUN ".\\" FILENAME
#else
#define LIBS "-lGLEW", "-lglfw", "-lGL"
#define FILENAME OUTPUT
#define RUN "./" OUTPUT
#endif

#define STB_IMAGE_URL "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"

#ifdef NDEBUG
#define CXXFLAGS "-DNDEBUG", "-std=c++17", "-g0", "-O3"
#else
#define CXXFLAGS "-Wall", "-Wextra", "-pedantic", "-std=c++17", "-ggdb", "-O0"
#endif

void build(const char* cxx)
{
    if (!PATH_EXISTS("src/stb_image.h"))
    {
        CMD("wget", STB_IMAGE_URL, "-O", "src/stb_image.h");
    }

#ifdef NDEBUG
    {
        char *vertex_shader_source = read_file_as_str("src/shaders/vertex.glsl");
        char *fragment_shader_source = read_file_as_str("src/shaders/fragment.glsl");

        FILE *f = fopen("src/baked_shaders.h", "wb");
        if (f == 0)
            PANIC("ERROR:%d: opening file %s\n", __LINE__, "src/baked_shaders.h");
        fprintf(f, "constexpr const char* VERTEX_SHADER_SOURCE = R\"(%s)\";\n", vertex_shader_source);
        fprintf(f, "constexpr const char* FRAGMENT_SHADER_SOURCE = R\"(%s)\";", fragment_shader_source);
        fclose(f);

        free(vertex_shader_source);
        free(fragment_shader_source);
    }
#endif

    CMD(cxx, SOURCES, CXXFLAGS, "-oopengl-playground", LIBS);
}

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);

    char *cxx = getenv("cxx");
    if (cxx == 0)
        cxx = "g++";

    if (argc > 1)
    {
        if (strcmp(argv[1], "run") == 0)
        {
            build(cxx);
            CMD(RUN);
        }
        else if (strcmp(argv[1], "fmt") == 0)
        {
            CMD("astyle", "src/*.cpp", "src/*.h", "-n", "-r", "--style=kr");
        }
    }
    else
    {
        build(cxx);
    }
}
