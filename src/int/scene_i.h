#pragma once
#include <GLFW/glfw3.h>

#include "../vbo.h"
#include "../cam.h"

typedef struct {

    vbo_t** vbo;
    cam_t** cam;

    // interaface
    void (*init  )(GLFWwindow* window);
    void (*update)();
    void (*draw  )();
    void (*free  )();

    // Interactive handlers
    void (*on_key         ) (int key, int scancode, int action, int mods);
    void (*on_mouse_move  ) (double xpos, double ypos);
    void (*on_scroll      ) (double xoffset, double yoffset);
    void (*on_mouse_button) (int button, int action, int mods);

} scene_i;