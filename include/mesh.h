#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vertex.h>

enum __mesh_enum{
    POSITION_VB,
    TEXCOORD_VB,

    NUM_BUFFERS
};

typedef struct __mesh_struct{
    GLuint vertex_array_object;
    GLuint vertex_array_buffers[NUM_BUFFERS];
    uint32_t draw_count;
} Mesh;

extern Mesh mesh(Vertex*, const uint32_t);
extern void mesh_draw(const Mesh*);

#define mesh_delete(__msh) glDeleteVertexArrays(1, &(__msh.vertex_array_object))


#endif