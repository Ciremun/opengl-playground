#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

#include "string.h"

#define SOURCES "main.cpp"
#define OUTPUT "opengl-playground"

#ifdef _WIN32
#define LIBS "-lglew32", "-lglfw3", "-lopengl32"
#define RUN ".\\" OUTPUT ".exe"
#else
#define LIBS "-lGLEW", "-lglfw", "-lGL"
#define RUN "./" OUTPUT
#endif

#define CXXFLAGS "-Wall", "-Wextra", "-pedantic", "-std=c++17", "-ggdb", "-O0"

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);

    char *cxx = getenv("cxx");
    if (cxx == NULL)
        cxx = "g++";
    CMD(cxx, SOURCES, CXXFLAGS, "-oopengl-playground", LIBS);
    if (argc > 1)
    {
        if (strcmp(argv[1], "run") == 0)
            CMD(RUN);
    }
}