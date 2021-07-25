#include <texture.h>
#include <GL/glew.h>
#include <assert.h>
#include <stb_image.h>
#include <signal.h>


Texture texture(const char* filename){
    Texture txt;

    unsigned int width, height, num_components;
    unsigned char* imagedata = stbi_load(filename, &width, &height, &num_components, 4);

    if(imagedata == NULL){
        fprintf(stderr, "Texture loading failed to load for texture: %s\n", filename);
        kill(0, SIGABRT);
    }

    glGenTextures(1, &txt);
    glBindTexture(GL_TEXTURE_2D, txt);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata);

    stbi_image_free(imagedata);

    return txt;
}

void texture_bind(const Texture txt, unsigned int unit){
    
    assert(unit >= 0 && unit <= 31);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, txt);
}


