#pragma once

#include "glad/glad.h"

typedef struct shader* shader_t;

shader_t shader_new();
shader_t shader_load(char* shadername);

void shader_free (shader_t shader);
void shader_set  (shader_t shader, const GLfloat* mvp, const GLfloat* col);
void shader_unset(shader_t shader);
