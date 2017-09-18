#pragma once

#include <stdint.h>
#include "kvec.h"

typedef struct {
    GLuint    id;
    uint32_t  parts_cnt;
    uint32_t  points_cnt;
    uint32_t* parts;
} vbo_t;
typedef vbo_t* vbo_p;

typedef struct {
    float x, y;
} point_t;
typedef kvec_t(point_t) points_v;
typedef kvec_t(points_v) parts_v;

vbo_p vbo_new();
void vbo_free(vbo_p vbo);
void vbo_fill(vbo_p vbo, parts_v* parts);
