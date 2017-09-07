#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow** win;
    void (*init)();
    void (*free)();
    void (*loop)(void (*loop)());

} glfw_i;