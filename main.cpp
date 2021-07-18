#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

// unsafe fn compile_shader(shader_id: GLuint, shader_c_string: &CStr) {
//     let mut compiled = 0;

//     gl::ShaderSource(shader_id, 1, &shader_c_string.as_ptr(), std::ptr::null());
//     gl::CompileShader(shader_id);

//     gl::GetShaderiv(shader_id, gl::COMPILE_STATUS, &mut compiled);

//     if compiled != gl::TRUE.into() {
//         let mut buffer: [u8; 1024] = [0; 1024];
//         let mut length: GLsizei = 0;
//         gl::GetShaderInfoLog(
//             shader_id,
//             buffer.len().try_into().unwrap(),
//             &mut length,
//             buffer.as_mut_ptr() as *mut i8,
//         );
//         panic!(
//             "Could not compile shader: {}",
//             std::str::from_utf8(&buffer[0..length as usize]).unwrap()
//         );
//     }
// }

// unsafe fn load_shaders() -> GLuint {
//     let vertex_shader_bytes = include_bytes!("shaders/vertex.glsl");
//     let fragment_shader_bytes = include_bytes!("shaders/fragment.glsl");

//     let mut vertex_shader_string = String::from_utf8_lossy(vertex_shader_bytes);
//     let mut fragment_shader_string = String::from_utf8_lossy(fragment_shader_bytes);

//     let vertex_shader_id = gl::CreateShader(gl::VERTEX_SHADER);
//     let fragment_shader_id = gl::CreateShader(gl::FRAGMENT_SHADER);

//     vertex_shader_string.to_mut().push('\0');
//     let vertex_shader_c_str = CStr::from_bytes_with_nul_unchecked(vertex_shader_string.as_bytes());
//     fragment_shader_string.to_mut().push('\0');
//     let fragment_shader_c_str =
//         CStr::from_bytes_with_nul_unchecked(fragment_shader_string.as_bytes());

//     compile_shader(vertex_shader_id, vertex_shader_c_str);
//     compile_shader(fragment_shader_id, fragment_shader_c_str);

//     let program_id = gl::CreateProgram();
//     gl::AttachShader(program_id, vertex_shader_id);
//     gl::AttachShader(program_id, fragment_shader_id);
//     gl::LinkProgram(program_id);

//     let mut linked = 0;
//     gl::GetProgramiv(program_id, gl::LINK_STATUS, &mut linked);

//     if linked != gl::TRUE.into() {
//         let mut buffer: [u8; 1024] = [0; 1024];
//         let mut length: GLsizei = 0;
//         gl::GetProgramInfoLog(
//             program_id,
//             buffer.len().try_into().unwrap(),
//             &mut length,
//             buffer.as_mut_ptr() as *mut i8,
//         );
//         panic!(
//             "Could not link shader: {}",
//             std::str::from_utf8(&buffer[0..length as usize]).unwrap()
//         );
//     }

//     gl::DetachShader(program_id, vertex_shader_id);
//     gl::DetachShader(program_id, fragment_shader_id);

//     gl::DeleteShader(vertex_shader_id);
//     gl::DeleteShader(fragment_shader_id);

//     return program_id;
// }

int main()
{
    GLFWwindow *window;

    if (!glfwInit())
        return 1;

    window = glfwCreateWindow(800, 800, "opengl-playground", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        return 1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(400, 400, 0));

    // program_id = load_shaders();
    // gl::UseProgram(program_id);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}