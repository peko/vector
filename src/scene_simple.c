#include "scene.h"

static vbo_t* vbo = NULL;

// interaface
static void init  (){};
static void update(){};
static void draw  (){};
static void free  (){};

// Interactive handlers
static void on_key         (GLFWwindow* window, int key, int scancode, int action, int mods){};
static void on_mouse_move  (GLFWwindow* window, double xpos, double ypos){};
static void on_scroll      (GLFWwindow* window, double xoffset, double yoffset){};
static void on_mouse_button(GLFWwindow* window, int button, int action, int mods){};

scene_t simple = {
    
    &vbo,

    //interface
    init,
    update,
    draw,
    free,
    
    // events
    on_key,
    on_mouse_move,
    on_scroll,
    on_mouse_button,
}