#include <stdio.h>
#include <stdbool.h>

#include "linmath.h"

#include "shader.h"
#include "render_i.h"

  //////////////
 /// STATIC ///
//////////////

static GLuint vertex_shader, fragment_shader, program;
static char* vertex_shader_text;
static char* fragment_shader_text;
static GLint mvp_location, pos_location, col_location;

static void 
_init() {

    shader_load("shaders/wire_shader.vert", &vertex_shader_text);
    shader_load("shaders/wire_shader.frag", &fragment_shader_text);

    // VERTEX    
    printf("vertext shader\n");
    printf("----\n%s\n----\n", vertex_shader_text);
    
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const char**)&vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    shader_check(vertex_shader);
    
    // FRAGMENT
    printf("fragment shader\n");
    printf("----\n%s\n----\n", fragment_shader_text);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const char**)&fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    shader_check(fragment_shader);

    // PROGRAMM

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "mvp");
    col_location = glGetUniformLocation(program, "col");
    pos_location = glGetAttribLocation(program, "pos");

    // cleanup shader texts
    free(vertex_shader_text);
    free(fragment_shader_text);
}

// draw loop
static void 
_draw(scene_i* scene) {

    cam_t* cam = *(scene->cam);
    vbo_t* vbo = *(scene->vbo);

    bool loop = true;
    vec3 col = {1.0, 1.0, 1.0};

    mat4x4 m, p, mvp;

    // SET BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);        

    // SET ATTRIBUTES
    glEnableVertexAttribArray(pos_location);
    glVertexAttribPointer(pos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(GLfloat)*2, (void*) 0);

    //glEnableVertexAttribArray(vcol_location);
    //glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
    //              sizeof(float) * 5, (void*) (sizeof(float) * 2));

    // SET VIEW
    mat4x4_identity(m);
    mat4x4_translate_in_place(m, cam->x, cam->y, 0.0);
    mat4x4_scale_aniso(m, m, cam->s, cam->s, cam->s);

    mat4x4_ortho(p, -cam->r, cam->r, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    // SET SHADER
    glUseProgram(program);
    // send view matrix
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
    glUniform3fv(col_location,  1, (const GLfloat*) col);

    // DRAW
    uint32_t start = 0;
    for(uint32_t i=0; i<vbo->parts_cnt; i++) {
        GLuint l = vbo->parts[i];
        glDrawArrays(loop?GL_LINE_LOOP:GL_LINE_STRIP, start, l);
        start+= l;
    }
    // whole at once
    // glDrawArrays(GL_LINE_LOOP, 0, vbo->vertices);

    // UNSET SHADER
    glUseProgram(0);

    // UNSET ATTRIBUTES
    glDisableVertexAttribArray(pos_location);

    // UNSET BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// cleanup at the end
static void 
_free() {
    // delete program from vm
    glDeleteProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

  //////////////
 /// GLOBAL ///
//////////////

render_i render_wire = {
    .init = _init,
    .free = _free,
    .draw = _draw
};