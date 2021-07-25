#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <cglm/cglm.h>

typedef struct __transform{
    vec3 pos;
    vec3 rot;
    vec3 scale;
} Transform;

extern void transform_model(mat4, Transform*);

#endif