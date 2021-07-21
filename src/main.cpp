#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <cstdio>
#include <string>
#include <unordered_map>

#include "shaders.h"

#define WIDTH 1024
#define HEIGHT 768

#define PANIC(fmt, ...)                                        \
    do                                                         \
    {                                                          \
        printf("ERROR: %d: " fmt "\n", __LINE__, __VA_ARGS__); \
        exit(1);                                               \
    } while (0)

std::unordered_map<std::string, int> m_UniformLocationCache;

int GetUniformLocation(GLuint program_id, const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    int location = glGetUniformLocation(program_id, name.c_str());
    if (location == -1)
        printf("Uniform %s doesn't exist", name.c_str());
    m_UniformLocationCache[name] = location;
    return location;
}

void compile_shader(GLuint shader_id, const char *shader_source)
{
    GLint compiled = false;

    glShaderSource(shader_id, 1, &shader_source, nullptr);
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE)
    {
        GLchar buffer[1024] = {0};
        GLsizei length = 0;
        glGetShaderInfoLog(shader_id, sizeof(buffer), &length, buffer);
        PANIC("Could not compile shader: %s", buffer);
    }
}

GLuint load_shaders()
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    compile_shader(vertex_shader_id, VERTEX_SHADER_SOURCE);
    compile_shader(fragment_shader_id, FRAGMENT_SHADER_SOURCE);

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    GLint linked = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked);

    if (linked != GL_TRUE)
    {
        GLchar buffer[1024] = {0};
        GLsizei length = 0;
        glGetProgramInfoLog(program_id, sizeof(buffer), &length, buffer);
        PANIC("Could not compile shader: %s", buffer);
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

int main()
{
    GLFWwindow *window;

    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(WIDTH, HEIGHT, "opengl-playground", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        return 1;
    }

    glfwSwapInterval(-1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    printf("%s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LESS);

    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    GLuint program_id = load_shaders();

    GLuint matrix_id = glGetUniformLocation(program_id, "MVP");
    GLuint time_id = glGetUniformLocation(program_id, "time");

    auto projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    auto model = glm::mat4(1.0f);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    static const GLfloat g_color_buffer_data[] = {
        0.583f, 0.771f, 0.014f,
        0.609f, 0.115f, 0.436f,
        0.327f, 0.483f, 0.844f,
        0.822f, 0.569f, 0.201f,
        0.435f, 0.602f, 0.223f,
        0.310f, 0.747f, 0.185f,
        0.597f, 0.770f, 0.761f,
        0.559f, 0.436f, 0.730f,
        0.359f, 0.583f, 0.152f,
        0.483f, 0.596f, 0.789f,
        0.559f, 0.861f, 0.639f,
        0.195f, 0.548f, 0.859f,
        0.014f, 0.184f, 0.576f,
        0.771f, 0.328f, 0.970f,
        0.406f, 0.615f, 0.116f,
        0.676f, 0.977f, 0.133f,
        0.971f, 0.572f, 0.833f,
        0.140f, 0.616f, 0.489f,
        0.997f, 0.513f, 0.064f,
        0.945f, 0.719f, 0.592f,
        0.543f, 0.021f, 0.978f,
        0.279f, 0.317f, 0.505f,
        0.167f, 0.620f, 0.077f,
        0.347f, 0.857f, 0.137f,
        0.055f, 0.953f, 0.042f,
        0.714f, 0.505f, 0.345f,
        0.783f, 0.290f, 0.734f,
        0.722f, 0.645f, 0.174f,
        0.302f, 0.455f, 0.848f,
        0.225f, 0.587f, 0.040f,
        0.517f, 0.713f, 0.338f,
        0.053f, 0.959f, 0.120f,
        0.393f, 0.621f, 0.362f,
        0.673f, 0.211f, 0.457f,
        0.820f, 0.883f, 0.371f,
        0.982f, 0.099f, 0.879f};

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    auto position = glm::vec3(2.6, 2.0, 3.5);

    float horizontal_angle = 3.15f;
    float vertical_angle = -0.63f;
    float speed = 5.0f;
    float mouse_speed = 0.1f;

    double dt;
    double last_frame = glfwGetTime();

    do
    {
        double current_frame = glfwGetTime();
        dt = current_frame - last_frame;
        last_frame = current_frame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program_id);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);

        auto direction = glm::vec3(glm::cos(vertical_angle) * glm::sin(horizontal_angle),
                                   glm::sin(vertical_angle),
                                   glm::cos(vertical_angle) * glm::cos(horizontal_angle));
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        horizontal_angle += mouse_speed * dt * ((float)WIDTH / 2.0f - xpos);
        vertical_angle += mouse_speed * dt * ((float)HEIGHT / 2.0f - ypos);

        auto right = glm::vec3(glm::sin(horizontal_angle - 3.14f / 2.0),
                               0.0f,
                               glm::cos(horizontal_angle - 3.14 / 2.0));

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position = position + direction * static_cast<float>(dt) * speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position = position - direction * static_cast<float>(dt) * speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position = position + right * static_cast<float>(dt) * speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position = position - right * static_cast<float>(dt) * speed;
        glfwSetCursorPos(window, (float)WIDTH / 2.0f, (float)HEIGHT / 2.0f);

        auto view = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
        auto mvp = projection * view * model;

        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);
        glUniform1f(time_id, current_frame);

        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return 0;
}