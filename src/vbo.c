#include <stdlib.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "vbo.h"

vbo_p
vbo_new() {
    vbo_p vbo = calloc(1, sizeof(vbo_t));
    return vbo;
}

void
vbo_fill(vbo_p vbo, parts_v* parts) {

    vbo->parts = (uint32_t*) calloc(parts->n, sizeof(uint32_t));

    // sum parts points
    vbo->points_cnt = 0;
    vbo->parts_cnt = parts->n;
    for(uint32_t s=0; s<parts->n; s++) {
        vbo->points_cnt += parts->a[s].n;
        vbo->parts[s] = parts->a[s].n;
    }

    // fill buffer
    point_t vertices[vbo->points_cnt];
    uint32_t i=0;
    for(uint32_t s=0; s<parts->n; s++) {
        for(uint32_t p=0; p<parts->a[s].n; p++) {
            point_t* pnt = &parts->a[s].a[p];
            vertices[i++] = (point_t) {pnt->x, pnt->y};
        }
    }

    // send buffer to vram
    glGenBuffers(1, &vbo->id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    glBufferData(GL_ARRAY_BUFFER,
        vbo->points_cnt * sizeof(point_t),
        vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
vbo_free(vbo_p vbo) {
    // clean up VRAM
    glDeleteBuffers(1, &vbo->id);
    // clean heap
    free(vbo->parts);
    free(vbo);
}
