#include <stdio.h>
#include <stdbool.h>

#include "linmath.h"

#include "shader.h"
#include "render_i.h"

  //////////////
 /// STATIC ///
//////////////

static shader_p shader;
static void 
_init() {
    shader = shader_load("wire_shader");
}

// draw loop
static void 
_draw(scene_i* scene) {

    cam_p cam = *(scene->cam);
    vbo_p vbo = *(scene->vbo);

    bool loop = true;
    vec3 col = {1.0, 1.0, 1.0};

    mat4x4 m, p, mvp;

    // SET BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);        

    // SET VIEW
    mat4x4_identity(m);
    mat4x4_translate_in_place(m, cam->x, cam->y, 0.0);
    mat4x4_scale_aniso(m, m, cam->s, cam->s, cam->s);
    mat4x4_ortho(p, -cam->r, cam->r, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    shader_set(shader, (const GLfloat*) mvp, (const GLfloat*) col);

    // DRAW
    uint32_t start = 0;
    for(uint32_t i=0; i<vbo->parts_cnt; i++) {
        GLuint l = vbo->parts[i];
        glDrawArrays(loop?GL_LINE_LOOP:GL_LINE_STRIP, start, l);
        start+= l;
    }
    // whole at once
    // glDrawArrays(GL_LINE_LOOP, 0, vbo->vertices);

    shader_unset(shader);

    // UNSET BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// cleanup at the end
static void 
_free(){
    shader_free(shader);
}

  //////////////
 /// GLOBAL ///
//////////////

render_i render_wire = {
    .init = _init,
    .free = _free,
    .draw = _draw
};
