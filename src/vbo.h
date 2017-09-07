#pragma once

#include <stdint.h>
#include "kvec.h"

typedef struct {
    GLuint    id;
    uint32_t  parts_cnt;
    uint32_t  points_cnt;
    uint32_t* parts;
} vbo_t;

typedef struct {
    float x, y;
} point_t;
typedef kvec_t(point_t) points_v;
typedef kvec_t(points_v) parts_v;

vbo_t* vbo_new();
void vbo_free(vbo_t* vbo);
void vbo_fill(vbo_t* vbo, parts_v* parts);
