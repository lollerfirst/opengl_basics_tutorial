#include <transform.h>

static vec3 axis[3] = {{1.0f, 0.0f, 0.0f},
                            {0.0f, 1.0f, 0.0f},
                            {0.0f, 0.0f, 1.0f}};

void transform_model(mat4 mat, Transform* trf){
    mat4 tmp[5];

    glm_translate_make(tmp[0], trf->pos);
    glm_rotate_make(tmp[1], trf->rot[0], axis[0]);
    glm_rotate_make(tmp[2], trf->rot[1], axis[1]);
    glm_rotate_make(tmp[3], trf->rot[2], axis[2]);
    glm_scale_make(tmp[4], trf->scale);

    mat4 rot;
    mat4* mat_arr[3] = {&tmp[1], &tmp[2], &tmp[3]};
    glm_mat4_mulN(mat_arr, 3, rot);

    glm_mat4_mul(tmp[0], rot, tmp[1]);
    glm_mat4_mul(tmp[1], tmp[4], mat);
}