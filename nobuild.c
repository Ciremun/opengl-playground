#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

#define SOURCES "main.cpp"

#ifdef _WIN32
#define LIBS "-lglew32", "-lglfw3", "-lopengl32"
#else
#define LIBS "-lGLEW", "-lglfw", "-lGL"
#endif

#define CXXFLAGS "-Wall", "-Wextra", "-pedantic", "-std=c++17", "-ggdb", "-O0"

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);

    char *cxx = getenv("cxx");
    if (cxx == NULL) cxx = "g++";
    CMD(cxx, SOURCES, CXXFLAGS, "-oopengl-playground", LIBS);
}