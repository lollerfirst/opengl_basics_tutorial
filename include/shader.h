#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <narg.h>
#include <stdarg.h>
#include <string.h>
#include <vector.h>
#include <transform.h>

enum __uniforms{
    TRANSFORM_U,

    NUM_UNIFORMS
};

#define NUM_SHADERS 2

typedef struct{
    GLuint h_program;
    GLuint h_shaders[NUM_SHADERS];
    GLuint h_uniforms[NUM_UNIFORMS];
} Shader;

extern Shader shader_init(const char*, GLenum, size_t, ...);
extern void shader_update(const Shader*, Transform*);

#define shader(filename, shader_type, ...) shader_init(filename, shader_type, PP_NARG(__VA_ARGS__),##__VA_ARGS__)

#define shader_bind(__sh) glUseProgram(__sh.h_program)

#define shader_delete(__sh) {\
    glDetachShader(__sh.h_program, __sh.h_shaders[0]);\
    glDetachShader(__sh.h_program, __sh.h_shaders[1]);\
    glDeleteProgram(__sh.h_program);\
    memset(&__sh, 0, sizeof(Shader));\
}



#endif /* SHADER_H */