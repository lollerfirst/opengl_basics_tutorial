#include <mesh.h>
#include <error.h>
#include <signal.h>
#include <vector.h>

Mesh mesh(Vertex* vertices, const uint32_t num_vertices){
    Mesh mesh = {.draw_count = num_vertices};

    glGenVertexArrays(1, &(mesh.vertex_array_object));
    glBindVertexArray(mesh.vertex_array_object);

    Vector positions_v;
    Vector tex_coord_v;
    vector_init(&positions_v, num_vertices, sizeof(vec3));
    vector_init(&tex_coord_v, num_vertices, sizeof(vec2));

    int32_t i;
    for (i = 0; i < num_vertices; ++i){
        vector_pushb(&positions_v, &vertices[i].pos);
        vector_pushb(&tex_coord_v, &vertices[i].tex_coord);
    }

    glGenBuffers(NUM_BUFFERS, mesh.vertex_array_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_array_buffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(vec3), vector_at(&positions_v, 0), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_array_buffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(vec2), vector_at(&tex_coord_v, 0), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
 
    glBindVertexArray(0);

    vector_free(&positions_v);
    vector_free(&tex_coord_v);

    return mesh;
}

void mesh_draw(const Mesh* mesh){

    glBindVertexArray(mesh->vertex_array_object);

    glDrawArrays(GL_TRIANGLES, 0, mesh->draw_count);

    glBindVertexArray(0);
}