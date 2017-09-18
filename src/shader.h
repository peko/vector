#pragma once

#include "glad/glad.h"

typedef struct shader* shader_p;

shader_p shader_new();
shader_p shader_load(char* shadername);

void shader_free (shader_p shader);
void shader_set  (shader_p shader, const GLfloat* mvp, const GLfloat* col);
void shader_unset(shader_p shader);
