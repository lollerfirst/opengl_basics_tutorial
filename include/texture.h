#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
typedef GLuint Texture;

#define texture_delete(x) glDeleteTextures(1, &x)

extern Texture texture(const char*);
extern void texture_bind(const Texture, unsigned int);


#endif