#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

typedef void (*void_cb           )(void);
typedef void (*on_error_cb       )(int error, const char* description);
typedef void (*on_key_cb         )(GLFWwindow* win, int key, int scancode, int action, int mods);
typedef void (*on_mouse_move_cb  )(GLFWwindow* win, double xpos, double ypos);
typedef void (*on_mouse_button_cb)(GLFWwindow* win, int button, int action, int mods);
typedef void (*on_scroll_cb      )(GLFWwindow* win, double xoffset, double yoffset);

typedef struct {
    GLFWwindow** win;
    void_cb init;
    void_cb free;
    void (*loop)(void (*loop)());

    on_error_cb        on_error       ;
    on_key_cb          on_key         ;
    on_mouse_move_cb   on_mouse_move  ;
    on_mouse_button_cb on_mouse_button;
    on_scroll_cb       on_scroll      ;
} glfw_i;
