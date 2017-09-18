#include <stdio.h>
#include <stdlib.h>

#include "shader.h"

struct shader {
    GLuint prog_ref;
    GLint mvp_loc, 
          pos_loc, 
          col_loc;
};

static char* load_file(char* filename);
static void shader_check(GLuint ref);
static void program_check(GLuint ref);

shader_p 
shader_new() {
    shader_p shader = calloc(1,sizeof(shader_p));
    return shader;
}

shader_p
shader_load(char* shadername) {

    shader_p shader = shader_new();

    char filename[256];
    
    sprintf(filename, "shaders/%s.vert", shadername);
    char* vert_buf = load_file(filename);
    
    sprintf(filename, "shaders/%s.frag", shadername);
    char* frag_buf = load_file(filename);

    // VERTEX    
    GLuint vert_ref = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource (vert_ref, 1, (const char**)&vert_buf, NULL);
    glCompileShader(vert_ref);
    shader_check   (vert_ref);
    
    // FRAGMENT
    GLuint frag_ref = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource (frag_ref, 1, (const char**)&frag_buf, NULL);
    glCompileShader(frag_ref);
    shader_check   (frag_ref);

    // PROGRAMM
    shader->prog_ref = glCreateProgram();
    glAttachShader(shader->prog_ref, vert_ref);
    glAttachShader(shader->prog_ref, frag_ref);
    glLinkProgram (shader->prog_ref);
    program_check (shader->prog_ref);
   
    shader->mvp_loc = glGetUniformLocation(shader->prog_ref, "mvp");
    shader->col_loc = glGetUniformLocation(shader->prog_ref, "col");
    shader->pos_loc = glGetAttribLocation (shader->prog_ref, "pos");

    // shaders can be deleted as soon it linked to program
    glDeleteShader (vert_ref);
    glDeleteShader (frag_ref);
    free(frag_buf);
    free(vert_buf);

    return shader;
}

static char* load_file(char* filename) {
    printf("Load shader: %s\n", filename);
    char* buffer = NULL;
    long length = 0;
    FILE* fp = fopen(filename, "rb");
    if(fp) {
        fseek (fp, 0, SEEK_END);
        length = ftell(fp);
        fseek (fp, 0, SEEK_SET);
        buffer = malloc(length+1);
        if (buffer) {
            fread(buffer, 1, length, fp);
        }
        fclose(fp);
        buffer[length]=0;
    }
    printf("%s", buffer);
    return buffer;    
}


static void shader_check(GLuint ref) {
    GLint status = 0;
    glGetShaderiv(ref, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(ref, GL_INFO_LOG_LENGTH, &maxLength);
        // The maxLength includes the NULL character
        GLchar error[maxLength];
        glGetShaderInfoLog(ref, maxLength, &maxLength, error);
        fprintf(stderr, "ERR: %s\n", error);
        // Provide the infolog in whatever manor you deem best.
        glDeleteShader(ref); // Don't leak the shader.
        return;
    }
}

static void program_check(GLuint ref) {
    GLint link_status, validate_status;
    glValidateProgram(ref);
    glGetProgramiv(ref, GL_LINK_STATUS    , &link_status    );
    glGetProgramiv(ref, GL_VALIDATE_STATUS, &validate_status);
    fprintf(stderr, "link %d\tvalidate %d\n", link_status, validate_status); 
    if(link_status == GL_FALSE || validate_status == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(ref, GL_INFO_LOG_LENGTH, &maxLength);
        // The maxLength includes the NULL character
        GLchar error[maxLength];
        glGetProgramInfoLog(ref, maxLength, &maxLength, error);
        fprintf(stderr, "ERR: %s\n", error);
        // Provide the infolog in whatever manor you deem best.
        glDeleteProgram(ref); // Don't leak the shader.
        return;
    }
}

void shader_free(shader_p shader) {
    // delete program from vm
    glDeleteProgram(shader->prog_ref);
    free(shader);
}

void shader_set(shader_p shader, const GLfloat* mvp, const GLfloat* col) {

    // SET ATTRIBUTES
    glEnableVertexAttribArray(shader->pos_loc);
    glVertexAttribPointer(shader->pos_loc, 2, GL_FLOAT, GL_FALSE,
                          sizeof(GLfloat)*2, (void*) 0);

    //glEnableVertexAttribArray(vcol_location);
    //glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
    //              sizeof(float) * 5, (void*) (sizeof(float) * 2));


    glUseProgram(shader->prog_ref);
    // send view matrix
    glUniformMatrix4fv(shader->mvp_loc, 1, GL_FALSE, (const GLfloat*) mvp);
    glUniform3fv      (shader->col_loc, 1, (const GLfloat*) col);
}

void shader_unset(shader_p shader) {
    // UNSET SHADER
    glUseProgram(0);
    // UNSET ATTRIBUTES
    glDisableVertexAttribArray(shader->pos_loc);
}
