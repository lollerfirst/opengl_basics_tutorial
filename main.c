#include <view.h>
#include <shader.h>
#include <mesh.h>
#include <vertex.h>
#include <texture.h>
#include <error.h>
#include <stdio.h>
#include <transform.h>
#include <math.h>


int main(){
    Display v = display(600, 800, "Hello World!");

    Vertex vertices[] = {{.pos = {-0.5, -0.5, 0}, .tex_coord = {0.0, 0.0}},
                        {.pos = {0, 0.5, 0}, .tex_coord = {0.5, 1.0}},
                        {.pos = {0.5, -0.5, 0}, .tex_coord = {1.0, 0.0}}};

    Shader sh = shader("./res/basicShader.vs", GL_VERTEX_SHADER, "./res/basicShader.fs", GL_FRAGMENT_SHADER);
    Mesh msh = mesh(vertices, sizeof(vertices) / sizeof(Vertex));
    Texture txt = texture("./res/bricks.jpg");
    
    float counter = 0.0f;
    while (!v.isclosed){

        float cosine = cosf(counter);
        Transform trf = {.pos = {sinf(counter), 0.0f, counter * 50},
                        .rot = {0.0f, 0.0f, 0.0f},
                        .scale = {cosine, cosine, cosine}};

        display_clear(0.0f, 0.15f, 0.3f, 1.0f);

        shader_bind(sh);

        shader_update(&sh, &trf);

        texture_bind(txt, 0);
        
        mesh_draw(&msh);
        
        display_update(&v);   

        counter += 0.01f;
    }
    
    mesh_delete(msh);
    shader_delete(sh);
    display_delete(&v);
    

    return 0;
}