#include <shader.h>

static void shader_error_unravel(const GLint, const GLint, const bool, const char*);
static Vector shader_load(const char*);
static GLuint shader_create(Vector, GLenum);

Shader shader_init(const char* filename, GLenum shader_type, size_t args, ...){
    Shader sh = {.h_program = glCreateProgram()};

    Vector source_shader = shader_load(filename);
    sh.h_shaders[0] = shader_create(source_shader, shader_type);
    glAttachShader(sh.h_program, sh.h_shaders[0]);

    bool is_filename = true;
    va_list list;
    va_start(list, args);
    int32_t i = 1;

    while ( args ){
        if ( is_filename ){
            vector_free(&source_shader);
            filename = (const char*) va_arg(list, uintptr_t);
            source_shader = shader_load(filename);
        }else{
            shader_type = va_arg(list, GLenum);
            sh.h_shaders[i] = shader_create(source_shader, shader_type);
            glAttachShader(sh.h_program, sh.h_shaders[i++]);
        }

        is_filename = !is_filename;
        --args;
    }

    va_end(list);
    vector_free(&source_shader);

    glBindAttribLocation(sh.h_program, 0, "position");
    glBindAttribLocation(sh.h_program, 1, "tex_coord");
    
    glLinkProgram(sh.h_program);
    shader_error_unravel(sh.h_program, GL_LINK_STATUS, true, "[CRITICAL] Program linking has failed: ");

    /* another validation of the program */
    glValidateProgram(sh.h_program);
    shader_error_unravel(sh.h_program, GL_VALIDATE_STATUS, true, "[CRITICAL] Program didn't pass validation: ");


    sh.h_uniforms[TRANSFORM_U] = glGetUniformLocation(sh.h_program, "transform");
    return sh;
}

static Vector shader_load(const char* filename){
    Vector data;
    vector_init(&data, 1024, sizeof(unsigned char));

    int32_t fd = open(filename, O_RDONLY);

    if (fd != -1){
        unsigned char tmp[256];
        ssize_t am;
        while ( (am = read(fd, tmp, 256)) != -1 && am != 0 )
            vector_pushn(&data, tmp, am);

        unsigned char c = '\0';
        vector_pushb(&data, &c);
        close(fd);
    }
    else
        vector_free(&data);

    return data;
}

static void shader_error_unravel(const GLint obj, const GLint flag, const bool isProgram, const char* error_message){
    GLint success = 0;
    GLchar error[1024] = { 0 };
    
    ( isProgram ) ?
        glGetProgramiv(obj, flag, &success) : 
        glGetShaderiv(obj, flag, &success);

    if ( success == GL_FALSE ){
        ( isProgram ) ? 
            glGetProgramInfoLog(obj, sizeof(error), NULL, error) : 
            glGetShaderInfoLog(obj, sizeof(error), NULL, error);

        fprintf(stderr, "%s: '%s'\n", error_message, error);
        kill(0, SIGABRT);
    }

}

static GLuint shader_create(Vector shader_source, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    
    if (shader == 0){
        fputs("[CRITICAL] Shader creation failed!\n", stderr);
        kill(0, SIGABRT);
    }

    unsigned char* ptr = vector_at(&shader_source, 0);

    GLsizei size = (GLsizei) vector_size(shader_source);

    glShaderSource(shader, 1, (const GLchar**) &ptr, &size);
    glCompileShader(shader);

    shader_error_unravel(shader, GL_COMPILE_STATUS, false, "[CRITICAL] Unable to compile shader: ");
    return shader;
}

void shader_update(const Shader* sh, Transform* trf){
    mat4 model;
    transform_model(model, trf);
    
    glUniformMatrix4fv(sh->h_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}
